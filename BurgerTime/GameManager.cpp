#include "GameManager.h"
#include "SceneManager.h"
#include "LevelCreator.h"
#include "LevelReader.h"

void GameManager::AddIngredient()
{
	++m_CurrentAmountIngredientsOnPlate;
	if (m_CurrentAmountIngredientsOnPlate == m_AmountOfIngredients)
	{
		NextScene();
		m_CurrentAmountIngredientsOnPlate = 0;
	}
}

void GameManager::SetGameMode(GameMode gameMode)
{
	m_GameMode = gameMode;
}

void GameManager::LoadUI(const std::shared_ptr<dae::Font>& font)
{
	auto highScore = std::make_shared<dae::GameObject>();
	highScore->GetComponent<dae::Transform>()->SetPosition(150.f, 5.f, 0.0f);
	auto hiScoreText = std::make_shared<dae::TextObject>(highScore, "HI-SCORE", font);
	hiScoreText->SetColor(SDL_Color{ 255, 0, 0, 255 });

	auto up = std::make_shared<dae::GameObject>();
	up->GetComponent<dae::Transform>()->SetPosition(50.f, 5.f, 0.0f);
	auto upText = std::make_shared<dae::TextObject>(up, "1UP", font);
	upText->SetColor(SDL_Color{ 255, 0, 0, 255 });

	auto pepperText = std::make_shared<dae::GameObject>();
	pepperText->GetComponent<dae::Transform>()->SetPosition(570.f, 10.f, 0.0f);
	pepperText->GetComponent<dae::Transform>()->SetSize(50.f, 15.f, 0.0f);
	auto pepperTextPic = dae::ResourceManager::GetInstance().LoadTexture("Sprites/PepperText.png");
	auto pepperTexture = std::make_shared<dae::TextureComponent>(pepperText, pepperTextPic);

	pepperText->AddComponent(pepperTexture);
	highScore->AddComponent(hiScoreText);
	up->AddComponent(upText);

	auto& sceneManager = dae::SceneManager::GetInstance();
	sceneManager.AddToCurrentScene(pepperText);
	sceneManager.AddToCurrentScene(highScore);
	sceneManager.AddToCurrentScene(up);
}

void GameManager::LoadLevel(const std::string& levelPath, const std::shared_ptr<PointComponent> score)
{
	auto levelReader = std::make_shared<LevelReader>();
	levelReader->ReadLevel(levelPath);
	auto levelObjects = LevelCreator::GetObjects();
	auto ingredients = LevelCreator::GetIngredients();
	for (size_t j = 0; j < ingredients.size(); ++j)
	{
		ingredients[j]->GetGameObject()->GetComponent<Ingredient>()->Initialize();
		ingredients[j]->GetGameObject()->GetComponent<Ingredient>()->AddObserver(score);
	}
	for (size_t i = 0; i < levelObjects.size(); ++i)
	{
		dae::SceneManager::GetInstance().AddToCurrentScene(levelObjects.at(i));
	}
	m_AmountOfIngredients = int(ingredients.size());
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

void GameManager::LoadPlayers(const glm::vec3& pos1, const glm::vec3& pos2)
{
	auto& sceneManager = dae::SceneManager::GetInstance();
	if (m_GameMode == GameMode::single)
	{
		auto player = InitializePlayer(0, pos1, "Sprites/PeterPepper.png", false);
		auto playerComponent = player->GetComponent<PlayerComponent>();
		auto attack = std::make_unique<AttackCommand>(playerComponent);
		auto moveRight = std::make_unique<MoveCommand>(playerComponent, PlayerDirection::right);
		auto moveUp = std::make_unique<MoveCommand>(playerComponent, PlayerDirection::up);
		auto moveDown = std::make_unique<MoveCommand>(playerComponent, PlayerDirection::down);
		auto moveLeft = std::make_unique<MoveCommand>(playerComponent, PlayerDirection::left);
		playerComponent->AddCommand(std::move(attack), SDL_SCANCODE_E, false);
		playerComponent->AddCommand(std::move(moveRight), SDL_SCANCODE_D, true);
		playerComponent->AddCommand(std::move(moveDown), SDL_SCANCODE_S, true);
		playerComponent->AddCommand(std::move(moveLeft), SDL_SCANCODE_A, true);
		playerComponent->AddCommand(std::move(moveUp), SDL_SCANCODE_W, true);
		sceneManager.AddToCurrentScene(player);
	}
	else if (m_GameMode == GameMode::multi)
	{
		auto player1 = InitializePlayer(0, pos1, "Sprites/PeterPepper.png", false);
		auto playerComponent1 = player1->GetComponent<PlayerComponent>();
		auto attack1 = std::make_unique<AttackCommand>(playerComponent1);
		auto moveRight1 = std::make_unique<MoveCommand>(playerComponent1, PlayerDirection::right);
		auto moveUp1 = std::make_unique<MoveCommand>(playerComponent1, PlayerDirection::up);
		auto moveDown1 = std::make_unique<MoveCommand>(playerComponent1, PlayerDirection::down);
		auto moveLeft1 = std::make_unique<MoveCommand>(playerComponent1, PlayerDirection::left);
		playerComponent1->AddCommand(std::move(attack1), SDL_SCANCODE_E, false);
		playerComponent1->AddCommand(std::move(moveRight1), SDL_SCANCODE_D, true);
		playerComponent1->AddCommand(std::move(moveDown1), SDL_SCANCODE_S, true);
		playerComponent1->AddCommand(std::move(moveLeft1), SDL_SCANCODE_A, true);
		playerComponent1->AddCommand(std::move(moveUp1), SDL_SCANCODE_W, true);

		auto player2 = InitializePlayer(1, pos2, "Sprites/MrsSalt.png", false, player1->GetComponent<HealthComponent>());
		auto playerComponent2 = player2->GetComponent<PlayerComponent>();
		auto attack2 = std::make_unique<AttackCommand>(playerComponent2);
		auto moveRight2 = std::make_unique<MoveCommand>(playerComponent2, PlayerDirection::right);
		auto moveUp2 = std::make_unique<MoveCommand>(playerComponent2, PlayerDirection::up);
		auto moveDown2 = std::make_unique<MoveCommand>(playerComponent2, PlayerDirection::down);
		auto moveLeft2 = std::make_unique<MoveCommand>(playerComponent2, PlayerDirection::left);
		playerComponent2->AddCommand(std::move(attack2), SDL_SCANCODE_E, false);
		playerComponent2->AddCommand(std::move(moveRight2), SDL_SCANCODE_RIGHT, true);
		playerComponent2->AddCommand(std::move(moveDown2), SDL_SCANCODE_DOWN, true);
		playerComponent2->AddCommand(std::move(moveLeft2), SDL_SCANCODE_LEFT, true);
		playerComponent2->AddCommand(std::move(moveUp2), SDL_SCANCODE_UP, true);

		sceneManager.AddToCurrentScene(player1);
		sceneManager.AddToCurrentScene(player2);
	}
	else
	{
		auto player1 = InitializePlayer(0, pos1, "Sprites/PeterPepper.png", false);
		auto playerComponent1 = player1->GetComponent<PlayerComponent>();
		auto attack1 = std::make_unique<AttackCommand>(playerComponent1);
		auto moveRight1 = std::make_unique<MoveCommand>(playerComponent1, PlayerDirection::right);
		auto moveUp1 = std::make_unique<MoveCommand>(playerComponent1, PlayerDirection::up);
		auto moveDown1 = std::make_unique<MoveCommand>(playerComponent1, PlayerDirection::down);
		auto moveLeft1 = std::make_unique<MoveCommand>(playerComponent1, PlayerDirection::left);
		playerComponent1->AddCommand(std::move(attack1), SDL_SCANCODE_E, false);
		playerComponent1->AddCommand(std::move(moveRight1), SDL_SCANCODE_D, true);
		playerComponent1->AddCommand(std::move(moveDown1), SDL_SCANCODE_S, true);
		playerComponent1->AddCommand(std::move(moveLeft1), SDL_SCANCODE_A, true);
		playerComponent1->AddCommand(std::move(moveUp1), SDL_SCANCODE_W, true);

		auto player2 = InitializePlayer(1, pos2, "Sprites/MrHotDog.png", true);
		auto playerComponent2 = player2->GetComponent<PlayerComponent>();
		auto attack2 = std::make_unique<AttackCommand>(playerComponent2);
		auto moveRight2 = std::make_unique<MoveCommand>(playerComponent2, PlayerDirection::right);
		auto moveUp2 = std::make_unique<MoveCommand>(playerComponent2, PlayerDirection::up);
		auto moveDown2 = std::make_unique<MoveCommand>(playerComponent2, PlayerDirection::down);
		auto moveLeft2 = std::make_unique<MoveCommand>(playerComponent2, PlayerDirection::left);
		playerComponent2->AddCommand(std::move(attack2), SDL_SCANCODE_E, false);
		playerComponent2->AddCommand(std::move(moveRight2), SDL_SCANCODE_RIGHT, true);
		playerComponent2->AddCommand(std::move(moveDown2), SDL_SCANCODE_DOWN, true);
		playerComponent2->AddCommand(std::move(moveLeft2), SDL_SCANCODE_LEFT, true);
		playerComponent2->AddCommand(std::move(moveUp2), SDL_SCANCODE_UP, true);

		sceneManager.AddToCurrentScene(player1);
		sceneManager.AddToCurrentScene(player2);
	}
}

//void GameManager::Update(float elapsedSec)
//{
//	if (m_StartWaiting)
//	{
//		m_CurrentTime += elapsedSec;
//		if (m_CurrentTime >= m_TotaWaitTime)
//		{
//			NextScene();
//			m_StartWaiting = false;
//			m_CurrentTime = 0.0f;
//		}
//	}
//}

void GameManager::NextScene()
{

	//if (m_CurrentTime >= m_TotaWaitTime)
	//{
	auto& sceneManager = dae::SceneManager::GetInstance();
	++m_NrScenes;
	//sceneManager.DeleteScene("Level " + std::to_string(m_NrScenes - 1));
	if (m_NrScenes == 4)
		m_NrScenes = 1;
	sceneManager.LoadScene("Level" + std::to_string(m_NrScenes));
	//}
	//else
		//m_StartWaiting = true;
}

std::shared_ptr<dae::GameObject> GameManager::InitializePlayer(int playerIdx, const glm::vec3& startPos, const std::string& texture, bool isEnemy, std::shared_ptr<HealthComponent> multiPlayer)
{
	int startLives{ 3 };
	auto player = std::make_shared<dae::GameObject>();
	auto playerComponent = std::make_shared<PlayerComponent>(player, startPos, playerIdx, isEnemy);

	if (!isEnemy)
	{
		if (multiPlayer != nullptr)
			player->AddComponent(multiPlayer);
		else
		{
			auto healthComponent = std::make_shared<HealthComponent>(player, startLives, glm::vec3{ 10.f, 10.f, 0.0f });
			player->AddComponent(healthComponent);
		}

		auto attackComponent = std::make_shared<PlayerAttackComponent>(player, 5);


		player->AddComponent(attackComponent);
	}

	auto collisionComponent = std::make_shared<dae::CollisionComponent>(player);

	auto picture = dae::ResourceManager::GetInstance().LoadTexture(texture);
	auto textureComponent = std::make_shared<dae::TextureComponent>(player, picture);

	std::shared_ptr<dae::AnimationComponent> animationComponent;
	if(!isEnemy)
		animationComponent = std::make_shared<dae::AnimationComponent>(player, 3, 6, 9, 1);
	else
		animationComponent = std::make_shared<dae::AnimationComponent>(player, 2, 6, 8, 1);

	auto movementComponent = std::make_shared<PlayerMovementComponent>(player, 50.0f);

	auto behaviourComponent = std::make_shared<CharacterBehaviour>(player);

	player->AddComponent(collisionComponent);
	player->AddComponent(animationComponent);
	player->AddComponent(textureComponent);
	player->AddComponent(movementComponent);
	player->AddComponent(behaviourComponent);

	player->AddComponent(playerComponent);

	return player;
}