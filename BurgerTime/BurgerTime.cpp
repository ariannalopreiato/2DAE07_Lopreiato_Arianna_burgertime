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

    auto pPointComponentOne = std::make_shared<PointComponent>(pPlayerOne, 0);

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

    auto picture = dae::ResourceManager::GetInstance().LoadTexture("../Data/Sprites/PeterPepper.png");
    auto pTextureComponentOne = std::make_shared<dae::TextureComponent>(pPlayerOne, picture);

    auto pAnimationComponentOne = std::make_shared<dae::AnimationComponent>(pPlayerOne, 3, 6, 9, 1);

    auto pMovementComponentOne = std::make_shared<PlayerMovementComponent>(pPlayerOne, 50.0f);

    auto pAttackComponentOne = std::make_shared<PlayerAttackComponent>(pPlayerOne, 5);

    pPlayerOne->AddComponent(pHealthComponentOne);
    pPlayerOne->AddComponent(pPointComponentOne);
    pPlayerOne->AddComponent(pCollisionComponentOne);
    pPlayerOne->AddComponent(pAnimationComponentOne);
    pPlayerOne->AddComponent(pTextureComponentOne);
    pPlayerOne->AddComponent(pMovementComponentOne);
    pPlayerOne->AddComponent(pAttackComponentOne);

    pPlayerOne->AddComponent(pPlayerComponentOne);

    dae::SoundSystem* soundSystem = new dae::SDL_SoundSystem();
    dae::ServiceLocator::RegisterSoundSystem(soundSystem);
    dae::ServiceLocator::GetSoundSystem().loadSound("../Data/RandomCoinSound.wav");

    auto levelReader = std::make_shared<LevelReader>();
    levelReader->ReadLevel("../Data/Level1.txt");
    auto levelObjects = LevelCreator::GetObjects();
    auto ingredients = LevelCreator::GetIngredients();
    for (size_t j = 0; j < ingredients.size(); ++j)
    {
        ingredients.at(j)->GetComponent<Ingredient>()->Initialize();
    }
    for (size_t i = 0; i < levelObjects.size(); ++i)
    {
        scene.Add(levelObjects.at(i));
    }

    auto hotDog = EnemyManager::SpawnMrHotDog(640.f, 407.f);

    scene.Add(hotDog);
    scene.Add(pPlayerOne);

    engine.Run();
    return 0;
}