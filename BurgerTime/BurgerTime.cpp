#include <windows.h>
#include <iostream>
#include <chrono>
#include <thread>
#include "BurgerTime.h"
#include "Minigin.h"
#include "MoveCommand.h"
#include "ControllerButton.h"
#include "KeyboardButton.h"
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
#include "Texture2D.h"
#include "AttackCommand.h"

int main(int, char* []) {

    //BurgerTime engine;
    //engine.Initialize();
    //engine.LoadGame();
    //engine.Run();
    //engine.Cleanup();
    dae::Minigin engine;
    engine.Initialize();
    auto& scene = dae::SceneManager::GetInstance().CreateScene("Demo");

    auto pPlayerOne = std::make_shared<dae::GameObject>();
    auto pPlayerComponentOne = std::make_shared<PlayerComponent>(pPlayerOne, 5);

    auto pHealthComponentOne = std::make_shared<HealthComponent>(pPlayerOne, 3);

    auto pPointComponentOne = std::make_shared<PointComponent>(pPlayerOne, 0);

    auto pCollisionComponentOne = std::make_shared<dae::CollisionComponent>(pPlayerOne, Rectf{ 0,0,200,200 });

    auto attack = std::make_unique<AttackCommand>(pPlayerComponentOne);
    auto moveRight = std::make_unique<MoveCommand>(pPlayerComponentOne, PlayerDirection::right);
    auto moveUp = std::make_unique<MoveCommand>(pPlayerComponentOne, PlayerDirection::up);
    auto moveDown = std::make_unique<MoveCommand>(pPlayerComponentOne, PlayerDirection::down);
    auto moveLeft = std::make_unique<MoveCommand>(pPlayerComponentOne, PlayerDirection::left);
    pPlayerComponentOne->AddCommand(std::move(attack), dae::ControllerButton::ButtonA, false, 0);
    pPlayerComponentOne->AddCommand(std::move(moveRight), dae::KeyboardButton::SDLK_d, true, 0);
    pPlayerComponentOne->AddCommand(std::move(moveDown), dae::KeyboardButton::SDLK_s, true, 0);
    pPlayerComponentOne->AddCommand(std::move(moveLeft), dae::KeyboardButton::SDLK_a, true, 0);
    pPlayerComponentOne->AddCommand(std::move(moveUp), dae::KeyboardButton::SDLK_w, true, 0);

    auto picture = dae::ResourceManager::GetInstance().LoadTexture("../Data/Sprites/PeterPepper.png");
    auto pTextureComponentOne = std::make_shared<dae::TextureComponent>(pPlayerOne, picture);

    auto pAnimationComponentOne = std::make_shared<dae::AnimationComponent>(pPlayerOne, 3, 6, 9, 1);

    auto pMovementComponentOne = std::make_shared<PlayerMovementComponent>(pPlayerOne, 40.0f);

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

    scene.Add(pPlayerOne);

    engine.Run();
    return 0;
}