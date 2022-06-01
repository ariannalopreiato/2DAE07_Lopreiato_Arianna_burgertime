#include <windows.h>
#include <iostream>
#include <chrono>
#include <thread>
#include "BurgerTime.h"
#include "Minigin.h"
#include "MoveCommand.h"
#include "ControllerButton.h"
#include "SoundSystem.h"
#include "ServiceLocator.h"
#include "SDL_SoundSystem.h"
#include "SceneManager.h"
#include "GameObject.h"
#include "TextObject.h"
#include "Scene.h"
#include "InputManager.h"
#include "Renderer.h"
#include "PlayerComponent.h"
#include "HealthComponent.h"
#include "PointComponent.h"
#include "CollisionComponent.h"
#include "TextureComponent.h"
#include "AnimationComponent.h"
#include "PlayerMovementComponent.h"
#include "PlayerAttackComponent.h"
#include "Ingredient.h"
#include "Texture2D.h"
#include "AttackCommand.h"
#include "LevelReader.h"
#include "LevelCreator.h"
#include "EnemyManager.h"

int main(int, char* []) {

    //BurgerTime engine;
    //engine.Initialize();
    //engine.LoadGame();
    //engine.Run();
    //engine.Cleanup();
    dae::Minigin engine;
    engine.Initialize();
    auto& scene = dae::SceneManager::GetInstance().CreateScene("Demo");

    //////player one initialization
    auto pPlayerOne = std::make_shared<dae::GameObject>();
    auto pPlayerComponentOne = std::make_shared<PlayerComponent>(pPlayerOne, 5);

    auto pHealthComponentOne = std::make_shared<HealthComponent>(pPlayerOne, 3);

    auto pCollisionComponentOne = std::make_shared<dae::CollisionComponent>(pPlayerOne);

    auto attack = std::make_unique<AttackCommand>(pPlayerComponentOne);
    auto moveRight = std::make_unique<MoveCommand>(pPlayerComponentOne, PlayerDirection::right);
    auto moveUp = std::make_unique<MoveCommand>(pPlayerComponentOne, PlayerDirection::up);
    auto moveDown = std::make_unique<MoveCommand>(pPlayerComponentOne, PlayerDirection::down);
    auto moveLeft = std::make_unique<MoveCommand>(pPlayerComponentOne, PlayerDirection::left);
    pPlayerComponentOne->AddCommand(std::move(attack), SDL_SCANCODE_SPACE, false, 0);
    pPlayerComponentOne->AddCommand(std::move(moveRight), SDL_SCANCODE_D, true, 0);
    pPlayerComponentOne->AddCommand(std::move(moveDown),SDL_SCANCODE_S, true, 0);
    pPlayerComponentOne->AddCommand(std::move(moveLeft), SDL_SCANCODE_A, true, 0);
    pPlayerComponentOne->AddCommand(std::move(moveUp), SDL_SCANCODE_W, true, 0);

    auto picture = dae::ResourceManager::GetInstance().LoadTexture("Sprites/PeterPepper.png");
    auto pTextureComponentOne = std::make_shared<dae::TextureComponent>(pPlayerOne, picture);

    auto pAnimationComponentOne = std::make_shared<dae::AnimationComponent>(pPlayerOne, 3, 6, 9, 1);

    auto pMovementComponentOne = std::make_shared<PlayerMovementComponent>(pPlayerOne, 50.0f);

    auto pAttackComponentOne = std::make_shared<PlayerAttackComponent>(pPlayerOne, 5);

    pPlayerOne->AddComponent(pHealthComponentOne);
    pPlayerOne->AddComponent(pCollisionComponentOne);
    pPlayerOne->AddComponent(pAnimationComponentOne);
    pPlayerOne->AddComponent(pTextureComponentOne);
    pPlayerOne->AddComponent(pMovementComponentOne);
    pPlayerOne->AddComponent(pAttackComponentOne);

    pPlayerOne->AddComponent(pPlayerComponentOne);

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
        ingredients[j]->GetComponent<Ingredient>()->Initialize();
        ingredients[j]->GetComponent<Ingredient>()->AddObserver(scoreComponent);
    }
    for (size_t i = 0; i < levelObjects.size(); ++i)
    {
        scene.Add(levelObjects.at(i));
    }

    auto hotDog = EnemyManager::SpawnMrHotDog(640.f, 408.f);
    //hotDog->GetComponent<EnemyComponent>()->AddObserver(scoreComponent);

    scene.Add(pepperText);
    scene.Add(highScore);
    scene.Add(up);
    scene.Add(pepperGO);
    scene.Add(scoreGO);
    scene.Add(hotDog);
    scene.Add(pPlayerOne);

    engine.Run();
    return 0;
}