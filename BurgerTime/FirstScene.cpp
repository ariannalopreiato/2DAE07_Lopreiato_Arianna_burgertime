#include "FirstScene.h"

FirstScene::FirstScene(const std::string& name)
	:Scene(name)
{}

void FirstScene::LoadSceneElements()
{
    int startLives{ 3 };
    auto pPlayerOne = std::make_shared<dae::GameObject>();
    auto pPlayerComponentOne = std::make_shared<PlayerComponent>(pPlayerOne, glm::vec3{ 50.0f, 350.f, 0.0f }, 0);

    auto pHealthComponentOne = std::make_shared<HealthComponent>(pPlayerOne, startLives, glm::vec3{ 10.f, 10.f, 0.0f });

    auto pCollisionComponentOne = std::make_shared<dae::CollisionComponent>(pPlayerOne);

    auto attack = std::make_unique<AttackCommand>(pPlayerComponentOne);
    auto moveRight = std::make_unique<MoveCommand>(pPlayerComponentOne, PlayerDirection::right);
    auto moveUp = std::make_unique<MoveCommand>(pPlayerComponentOne, PlayerDirection::up);
    auto moveDown = std::make_unique<MoveCommand>(pPlayerComponentOne, PlayerDirection::down);
    auto moveLeft = std::make_unique<MoveCommand>(pPlayerComponentOne, PlayerDirection::left);
    pPlayerComponentOne->AddCommand(std::move(attack), SDL_SCANCODE_E, false);
    pPlayerComponentOne->AddCommand(std::move(moveRight), SDL_SCANCODE_D, true);
    pPlayerComponentOne->AddCommand(std::move(moveDown), SDL_SCANCODE_S, true);
    pPlayerComponentOne->AddCommand(std::move(moveLeft), SDL_SCANCODE_A, true);
    pPlayerComponentOne->AddCommand(std::move(moveUp), SDL_SCANCODE_W, true);

    auto picture = dae::ResourceManager::GetInstance().LoadTexture("Sprites/PeterPepper.png");
    auto pTextureComponentOne = std::make_shared<dae::TextureComponent>(pPlayerOne, picture);

    auto pAnimationComponentOne = std::make_shared<dae::AnimationComponent>(pPlayerOne, 3, 6, 9, 1);

    auto pMovementComponentOne = std::make_shared<PlayerMovementComponent>(pPlayerOne, 50.0f);

    auto pAttackComponentOne = std::make_shared<PlayerAttackComponent>(pPlayerOne, 5);

    auto pBehaviourComponentOne = std::make_shared<CharacterBehaviour>(pPlayerOne);

    pPlayerOne->AddComponent(pHealthComponentOne);
    pPlayerOne->AddComponent(pCollisionComponentOne);
    pPlayerOne->AddComponent(pAnimationComponentOne);
    pPlayerOne->AddComponent(pTextureComponentOne);
    pPlayerOne->AddComponent(pMovementComponentOne);
    pPlayerOne->AddComponent(pAttackComponentOne);
    pPlayerOne->AddComponent(pBehaviourComponentOne);

    pPlayerOne->AddComponent(pPlayerComponentOne);

    //----------------------------------------Lives display
    for (size_t i = 0; i < size_t(startLives); ++i)
    {
        auto health = pHealthComponentOne->SpawnLife();
        Add(health);
    }
    //------------------------------------------------------

    //////player two initialization
    //auto pPlayerTwo = std::make_shared<dae::GameObject>();
    //auto pPlayerComponentTwo = std::make_shared<PlayerComponent>(pPlayerTwo, 1);

    //auto pHealthComponentTwo = std::make_shared<HealthComponent>(pPlayerTwo, 3);

    //auto pCollisionComponentTwo = std::make_shared<dae::CollisionComponent>(pPlayerTwo);

    //auto attack2 = std::make_unique<AttackCommand>(pPlayerComponentTwo);
    //auto moveRight2 = std::make_unique<MoveCommand>(pPlayerComponentTwo, PlayerDirection::right);
    //auto moveUp2 = std::make_unique<MoveCommand>(pPlayerComponentTwo, PlayerDirection::up);
    //auto moveDown2 = std::make_unique<MoveCommand>(pPlayerComponentTwo, PlayerDirection::down);
    //auto moveLeft2 = std::make_unique<MoveCommand>(pPlayerComponentTwo, PlayerDirection::left);
    //pPlayerComponentTwo->AddCommand(std::move(attack2), dae::ControllerButton::ButtonA, false);
    //pPlayerComponentTwo->AddCommand(std::move(moveRight), SDL_SCANCODE_RIGHT, true);
    //pPlayerComponentTwo->AddCommand(std::move(moveDown), SDL_SCANCODE_DOWN, true);
    //pPlayerComponentTwo->AddCommand(std::move(moveLeft), SDL_SCANCODE_LEFT, true);
    //pPlayerComponentTwo->AddCommand(std::move(moveUp), SDL_SCANCODE_UP, true);

    //auto picture2 = dae::ResourceManager::GetInstance().LoadTexture("Sprites/MrsSalt.png");
    //auto pTextureComponentTwo = std::make_shared<dae::TextureComponent>(pPlayerTwo, picture2);

    //auto pAnimationComponentTwo = std::make_shared<dae::AnimationComponent>(pPlayerTwo, 3, 6, 9, 1);

    //auto pMovementComponentTwo = std::make_shared<PlayerMovementComponent>(pPlayerTwo, 50.0f);

    //auto pAttackComponentTwo = std::make_shared<PlayerAttackComponent>(pPlayerTwo, 5);

    //auto pBehaviourComponentTwo = std::make_shared<CharacterBehaviour>(pPlayerTwo);

    //pPlayerTwo->AddComponent(pHealthComponentTwo);
    //pPlayerTwo->AddComponent(pCollisionComponentTwo);
    //pPlayerTwo->AddComponent(pAnimationComponentTwo);
    //pPlayerTwo->AddComponent(pTextureComponentTwo);
    //pPlayerTwo->AddComponent(pMovementComponentTwo);
    //pPlayerTwo->AddComponent(pAttackComponentTwo);
    //pPlayerTwo->AddComponent(pBehaviourComponentTwo);

    //pPlayerTwo->AddComponent(pPlayerComponentTwo);

    //------------------------------------------------------UI
    auto highScore = std::make_shared<dae::GameObject>();
    highScore->GetComponent<dae::Transform>()->SetPosition(150.f, 5.f, 0.0f);
    auto font = dae::ResourceManager::GetInstance().LoadFont("../Data/RetroGaming.ttf", 20);
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

    //------------------------------------------------------Score component
    auto scoreGO = std::make_shared<dae::GameObject>();
    auto scoreComponent = std::make_shared<PointComponent>(scoreGO, 0, glm::vec3{ 170.f, 30.f, 0.0f });
    auto textPoint = std::make_shared<dae::TextObject>(scoreGO, "0", font);
    textPoint->SetColor(SDL_Color{ 255, 255, 255, 255 });
    scoreGO->AddComponent(textPoint);
    scoreGO->AddComponent(scoreComponent);

    //------------------------------------------------------Pepper component
    auto pepperGO = std::make_shared<dae::GameObject>();
    auto pepperComponent = std::make_shared<PointComponent>(pepperGO, 0, glm::vec3{ 600.f, 30.f, 0.0f });
    auto pepperAmount = std::make_shared<dae::TextObject>(pepperGO, "5", font);
    pepperAmount->SetColor(SDL_Color{ 255, 255, 255, 255 });
    pepperGO->AddComponent(pepperAmount);
    pepperGO->AddComponent(pepperComponent);

    //------------------------------------------------------Lives component
    //auto livesGO = std::make_shared<dae::GameObject>();
    //auto pepperComponent = std::make_shared<PointComponent>(pepperGO, 0, glm::vec3{ 600.f, 30.f, 0.0f });
    //auto pepperAmount = std::make_shared<dae::TextObject>(pepperGO, "5", font);
    //pepperAmount->SetColor(SDL_Color{ 255, 255, 255, 255 });
    //pepperGO->AddComponent(pepperAmount);
    //pepperGO->AddComponent(pepperComponent);


    dae::SoundSystem* soundSystem = new dae::SDL_SoundSystem();
    dae::ServiceLocator::RegisterSoundSystem(soundSystem);
    dae::ServiceLocator::GetSoundSystem().loadSound("../Data/RandomCoinSound.wav");

    auto levelReader = std::make_shared<LevelReader>();
    levelReader->ReadLevel("../Data/Level1.txt");
    auto levelObjects = LevelCreator::GetObjects();
    auto ingredients = LevelCreator::GetIngredients();
    for (size_t j = 0; j < ingredients.size(); ++j)
    {
        ingredients[j]->GetGameObject()->GetComponent<Ingredient>()->Initialize();
        ingredients[j]->GetGameObject()->GetComponent<Ingredient>()->AddObserver(scoreComponent);
    }
    for (size_t i = 0; i < levelObjects.size(); ++i)
    {
        Add(levelObjects.at(i));
    }

   EnemyManager::SpawnAllLevelEnemies("../Data/EnemiesLevel1.txt");
    auto levelEnemies = EnemyManager::GetEnemies();
    for (size_t enemies = 0; enemies < levelEnemies.size(); ++enemies)
    {
        Add(levelEnemies[enemies]);
    }

    Add(pepperText);
    Add(highScore);
    Add(up);
    Add(pepperGO);
    Add(scoreGO);
    Add(pPlayerOne);
}
