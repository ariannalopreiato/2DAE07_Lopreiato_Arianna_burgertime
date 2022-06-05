#include "GameManager.h"
#include "SceneManager.h"
#include "LevelCreator.h"
#include "LevelReader.h"
#include "InputManager.h"

void GameManager::InputSetup(InputMethod inputOne, InputMethod inputTwo)
{
	m_InputOne = inputOne;
	m_InputTwo = inputTwo;
}

void GameManager::AddIngredient()
{
	++m_CurrentAmountIngredientsOnPlate;
	if (m_CurrentAmountIngredientsOnPlate == m_AmountOfIngredients)
	{
		NextScene();
		m_CurrentAmountIngredientsOnPlate = 0;
	}
}

void GameManager::NextScene()
{
	dae::InputManager::GetInstance().CleanCommands();
	LevelCreator::CleanLevel();
	EnemyManager::CleanEnemies();
	auto& sceneManager = dae::SceneManager::GetInstance();
	++m_NrScenes;
	if (m_NrScenes == 4)
		m_NrScenes = 1;
	sceneManager.SetLevelToLoad("Level" + std::to_string(m_NrScenes));
}

void GameManager::SetGameMode(GameMode gameMode)
{
	m_GameMode = gameMode;
}

void GameManager::LoadUI()
{
	auto font = dae::ResourceManager::GetInstance().LoadFont("../Data/RetroGaming.ttf", 20);

	auto up = std::make_shared<dae::GameObject>();
	up->GetComponent<dae::Transform>()->SetPosition(50.f, 5.f, 0.0f);
	auto upText = std::make_shared<dae::TextObject>(up, "1UP", font);
	upText->SetColor(SDL_Color{ 255, 0, 0, 255 });

	//------------------------------------------------------Score component
	auto highScore = std::make_shared<dae::GameObject>();
	highScore->GetComponent<dae::Transform>()->SetPosition(150.f, 5.f, 0.0f);
	auto hiScoreText = std::make_shared<dae::TextObject>(highScore, "HI-SCORE", font);
	hiScoreText->SetColor(SDL_Color{ 255, 0, 0, 255 });
	auto scoreGO = std::make_shared<dae::GameObject>();
	auto scoreComponent = std::make_shared<PointComponent>(scoreGO, 0, glm::vec3{ 170.f, 30.f, 0.0f });
	auto textPoint = std::make_shared<dae::TextObject>(scoreGO, "0", font);
	textPoint->SetColor(SDL_Color{ 255, 255, 255, 255 });
	scoreGO->AddComponent(textPoint);
	scoreGO->AddComponent(scoreComponent);

	//------------------------------------------------------Pepper component
	//text saying "pepper"
	auto pepperText = std::make_shared<dae::GameObject>();
	pepperText->GetComponent<dae::Transform>()->SetPosition(570.f, 10.f, 0.0f);
	pepperText->GetComponent<dae::Transform>()->SetSize(50.f, 15.f, 0.0f);
	auto pepperTextPic = dae::ResourceManager::GetInstance().LoadTexture("Sprites/PepperText.png");
	auto pepperTexture = std::make_shared<dae::TextureComponent>(pepperText, pepperTextPic);
	//amount of pepper
	auto pepperGO = std::make_shared<dae::GameObject>();
	auto pepperComponent = std::make_shared<PointComponent>(pepperGO, 0, glm::vec3{ 600.f, 30.f, 0.0f });
	auto pepperAmount = std::make_shared<dae::TextObject>(pepperGO, "5", font);
	pepperAmount->SetColor(SDL_Color{ 255, 255, 255, 255 });
	pepperGO->AddComponent(pepperAmount);
	pepperGO->AddComponent(pepperComponent);

	//------------------------------------------------------Lives component
	auto livesGO = std::make_shared<dae::GameObject>();
	livesGO->GetComponent<dae::Transform>()->SetPosition(glm::vec3{ 10.f, 10.f, 0.0f });
	auto livesComponent = std::make_shared<HealthComponent>(livesGO, 3);
	livesGO->AddComponent(livesComponent);

	pepperText->AddComponent(pepperTexture);
	highScore->AddComponent(hiScoreText);
	up->AddComponent(upText);

	//This game objects need to stay the same through out the whole game without being reset when loading a new level
	auto& sceneManager = dae::SceneManager::GetInstance();
	sceneManager.AddSharedObject(pepperText);
	sceneManager.AddSharedObject(highScore);
	sceneManager.AddSharedObject(up);
	sceneManager.AddSharedObject(scoreGO);
	sceneManager.AddSharedObject(pepperGO);
	sceneManager.AddSharedObject(livesGO);
	m_ScoreComponent = scoreComponent;
	m_HealthComponent = livesComponent;
	m_PepperComponent = pepperComponent;
}

void GameManager::LoadLevel(const std::string& levelPath)
{
	auto levelReader = std::make_shared<LevelReader>();
	levelReader->ReadLevel(levelPath);
	auto levelObjects = LevelCreator::GetObjects();
	auto ingredients = LevelCreator::GetIngredients();
	for (size_t j = 0; j < ingredients.size(); ++j)
	{
		ingredients[j]->GetGameObject()->GetComponent<Ingredient>()->Initialize();
		ingredients[j]->GetGameObject()->GetComponent<Ingredient>()->AddObserver(m_ScoreComponent.lock());
	}
	for (size_t i = 0; i < levelObjects.size(); ++i)
	{
		dae::SceneManager::GetInstance().AddToCurrentScene(levelObjects.at(i));
	}
	//m_AmountOfIngredients = int(ingredients.size());
	m_AmountOfIngredients = 1;
}

void GameManager::LoadEnemies(const std::string& enemiesPath)
{
	EnemyManager::SpawnAllLevelEnemies(enemiesPath);
	auto levelEnemies = EnemyManager::GetEnemies();
	for (size_t enemies = 0; enemies < levelEnemies.size(); ++enemies)
	{
		dae::SceneManager::GetInstance().AddToCurrentScene(levelEnemies[enemies]);
	}
}

void GameManager::LoadPlayersAndEnemies(const glm::vec3& pos1, const std::string& enemiesPath, const glm::vec3& pos2)
{
	auto& sceneManager = dae::SceneManager::GetInstance();
	if (m_GameMode == GameMode::single)
	{
		auto player = InitializePlayer(0, pos1, "Sprites/PeterPepper.png", false);
		auto playerComponent = player->GetComponent<PlayerComponent>();
		if (m_InputOne == InputMethod::keyboard)
			SetUpInputKeyboard(playerComponent, 0);
		else
			SetUpInputController(playerComponent);

		sceneManager.AddToCurrentScene(player);
		LoadEnemies(enemiesPath);
	}
	else if (m_GameMode == GameMode::multi)
	{
		auto player1 = InitializePlayer(0, pos1, "Sprites/PeterPepper.png", false);
		auto playerComponent1 = player1->GetComponent<PlayerComponent>();
		if (m_InputOne == InputMethod::keyboard)
			SetUpInputKeyboard(playerComponent1, 0);
		else
			SetUpInputController(playerComponent1);

		auto player2 = InitializePlayer(1, pos2, "Sprites/MrsSalt.png", false);
		auto playerComponent2 = player2->GetComponent<PlayerComponent>();
		if (m_InputTwo == InputMethod::keyboard)
			SetUpInputKeyboard(playerComponent2, 1);
		else
			SetUpInputController(playerComponent2);
		

		sceneManager.AddToCurrentScene(player1);
		sceneManager.AddToCurrentScene(player2);
		LoadEnemies(enemiesPath);
	}
	else
	{
		auto player1 = InitializePlayer(0, pos1, "Sprites/PeterPepper.png", false);
		auto playerComponent1 = player1->GetComponent<PlayerComponent>();
		if (m_InputOne == InputMethod::keyboard)
			SetUpInputKeyboard(playerComponent1, 0);
		else
			SetUpInputController(playerComponent1);

		auto player2 = InitializePlayer(1, pos2, "Sprites/MrHotDog.png", true, player1);
		auto playerComponent2 = player2->GetComponent<PlayerComponent>();
		if (m_InputTwo == InputMethod::keyboard)
			SetUpInputKeyboard(playerComponent2, 1);
		else
			SetUpInputController(playerComponent2);


		sceneManager.AddToCurrentScene(player1);
		sceneManager.AddToCurrentScene(player2);
	}
}

std::shared_ptr<PointComponent> GameManager::GetScoreComponent()
{
	return m_ScoreComponent.lock();
}

void GameManager::SetUpInputKeyboard(const std::shared_ptr<PlayerComponent>& player, int playerIdx)
{
	auto attack = std::make_unique<AttackCommand>(player);
	auto moveRight = std::make_unique<MoveCommand>(player, PlayerDirection::right);
	auto moveUp = std::make_unique<MoveCommand>(player, PlayerDirection::up);
	auto moveDown = std::make_unique<MoveCommand>(player, PlayerDirection::down);
	auto moveLeft = std::make_unique<MoveCommand>(player, PlayerDirection::left);
	if (playerIdx == 0)
	{
		player->AddCommand(std::move(attack), SDL_SCANCODE_E, false);
		player->AddCommand(std::move(moveRight), SDL_SCANCODE_D, true);
		player->AddCommand(std::move(moveDown), SDL_SCANCODE_S, true);
		player->AddCommand(std::move(moveLeft), SDL_SCANCODE_A, true);
		player->AddCommand(std::move(moveUp), SDL_SCANCODE_W, true);
	}
	else
	{
		player->AddCommand(std::move(attack), SDL_SCANCODE_SPACE, false);
		player->AddCommand(std::move(moveRight), SDL_SCANCODE_RIGHT, true);
		player->AddCommand(std::move(moveDown), SDL_SCANCODE_DOWN, true);
		player->AddCommand(std::move(moveLeft), SDL_SCANCODE_LEFT, true);
		player->AddCommand(std::move(moveUp), SDL_SCANCODE_UP, true);
	}
}

void GameManager::SetUpInputController(const std::shared_ptr<PlayerComponent>& player)
{
	auto attack = std::make_unique<AttackCommand>(player);
	auto moveRight = std::make_unique<MoveCommand>(player, PlayerDirection::right);
	auto moveUp = std::make_unique<MoveCommand>(player, PlayerDirection::up);
	auto moveDown = std::make_unique<MoveCommand>(player, PlayerDirection::down);
	auto moveLeft = std::make_unique<MoveCommand>(player, PlayerDirection::left);
	player->AddCommand(std::move(attack), dae::ControllerButton::ButtonA, false);
	player->AddCommand(std::move(moveRight), dae::ControllerButton::ButtonRight, true);
	player->AddCommand(std::move(moveDown), dae::ControllerButton::ButtonDown, true);
	player->AddCommand(std::move(moveLeft), dae::ControllerButton::ButtonLeft, true);
	player->AddCommand(std::move(moveUp), dae::ControllerButton::ButtonUp, true);
}

std::shared_ptr<dae::GameObject> GameManager::InitializePlayer(int playerIdx, const glm::vec3& startPos, const std::string& texture, bool isEnemy, std::shared_ptr<dae::GameObject> otherPlayer)
{
	auto player = std::make_shared<dae::GameObject>();
	auto playerComponent = std::make_shared<PlayerComponent>(player, startPos, playerIdx, isEnemy, otherPlayer);

	auto collisionComponent = std::make_shared<dae::CollisionComponent>(player);

	auto picture = dae::ResourceManager::GetInstance().LoadTexture(texture);
	auto textureComponent = std::make_shared<dae::TextureComponent>(player, picture);

	std::shared_ptr<dae::AnimationComponent> animationComponent;
	float speed{};
	if (!isEnemy)
	{
		animationComponent = std::make_shared<dae::AnimationComponent>(player, 3, 6, 9, 1);
		speed = 50.f;
		auto attackComponent = std::make_shared<PlayerAttackComponent>(player, 5);
		player->AddComponent(attackComponent);
		playerComponent->AddObserver(m_HealthComponent.lock());
	}
	else
	{
		animationComponent = std::make_shared<dae::AnimationComponent>(player, 2, 6, 8, 1);
		speed = 40.f;
	}

	auto movementComponent = std::make_shared<PlayerMovementComponent>(player, speed);

	auto behaviourComponent = std::make_shared<CharacterBehaviour>(player);

	player->AddComponent(collisionComponent);
	player->AddComponent(animationComponent);
	player->AddComponent(textureComponent);
	player->AddComponent(movementComponent);
	player->AddComponent(behaviourComponent);
	player->AddComponent(playerComponent);

	return player;
}