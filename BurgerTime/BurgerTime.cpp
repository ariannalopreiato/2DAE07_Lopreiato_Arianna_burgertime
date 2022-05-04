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
#include "InputComponent.h"
#include "AttackCommand.h"

int main(int, char* []) {

    //BurgerTime engine;
    //engine.Initialize();
    //engine.LoadGame();
    //engine.Run();
    //engine.Cleanup();
    dae::Minigin engine;
    engine.Initialize();

    auto pPlayerOne = std::make_shared<dae::GameObject>();
    auto pPlayerComponentOne = std::make_shared<PlayerComponent>(pPlayerOne, 5);
    auto pHealthComponentOne = std::make_shared<HealthComponent>(pPlayerOne, 3);
    auto pPointComponentOne = std::make_shared<PointComponent>(pPlayerOne, 0);
    auto pCollisionComponentOne = std::make_shared<CollisionComponent>(pPlayerOne, Rectf{ 0,0,20,20 });
    auto pInputComponentOne = std::make_shared<InputComponent>(pPlayerOne, 0);
    auto attack = std::make_unique<AttackCommand>(pPlayerComponentOne);
    pInputComponentOne->AddCommand(std::move(attack), dae::ControllerButton::ButtonA);
    auto moveRight = std::make_unique<MoveCommand>(pPlayerComponentOne);
    pInputComponentOne->AddCommand(std::move(moveRight), dae::ControllerButton::ButtonB);
    pPlayerOne->AddComponent(pPlayerComponentOne);
    pPlayerOne->AddComponent(pHealthComponentOne);
    pPlayerOne->AddComponent(pPointComponentOne);
    pPlayerOne->AddComponent(pCollisionComponentOne);
    pPlayerOne->AddComponent(pInputComponentOne);


    dae::SoundSystem* soundSystem = new dae::SDL_SoundSystem();
    dae::ServiceLocator::RegisterSoundSystem(soundSystem);
    dae::ServiceLocator::GetSoundSystem().loadSound("../Data/RandomCoinSound.wav");
    auto& renderer = dae::Renderer::GetInstance();
    auto& sceneManager = dae::SceneManager::GetInstance();
    auto& input = dae::InputManager::GetInstance();

    bool doContinue = true;
    auto lastTime = std::chrono::high_resolution_clock::now();
    while (doContinue)
    {
        const auto currentTime = std::chrono::high_resolution_clock::now();
        float deltaTime = std::chrono::duration<float>(currentTime - lastTime).count();
        doContinue = input.ProcessInput();
        sceneManager.Update(deltaTime);
        renderer.Render();
        lastTime = currentTime;
    }

    return 0;
}

//void BurgerTime::Initialize()
//{
//    m_MiniginEngine.Initialize();
//}
//
//void BurgerTime::Cleanup()
//{
//    m_MiniginEngine.Cleanup();
//}
//
//void BurgerTime::LoadGame() const
//{
//    auto pPlayerOne = std::make_shared<Player>(0);
//    CommandManager commandManagerOne = CommandManager(pPlayerOne);
//    commandManagerOne.SetMoveCommandsController(dae::ControllerButton::ButtonY, dae::ControllerButton::ButtonA, dae::ControllerButton::ButtonX, dae::ControllerButton::ButtonB);
//
//    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
//    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
//        std::cout << "Error: " << Mix_GetError() << std::endl;
//    dae::SoundSystem* soundSystem = new dae::SDL_SoundSystem();
//    dae::ServiceLocator::RegisterSoundSystem(soundSystem);
//    dae::ServiceLocator::GetSoundSystem().loadSound("../Data/RandomCoinSound.wav");
//
//    pPlayerOne->Update(m_ElapsedTime);
//}
//
//void BurgerTime::Run()
//{
//    LoadGame();
//
//    auto& renderer = dae::Renderer::GetInstance();
//    auto& sceneManager = dae::SceneManager::GetInstance();
//    auto& input = dae::InputManager::GetInstance();
//
//    bool doContinue = true;
//    auto lastTime = std::chrono::high_resolution_clock::now();
//    while (doContinue)
//    {
//        const auto currentTime = std::chrono::high_resolution_clock::now();
//        float deltaTime = std::chrono::duration<float>(currentTime - lastTime).count();
//        doContinue = input.ProcessInput();
//        sceneManager.Update(deltaTime);
//        renderer.Render();
//        lastTime = currentTime;
//        m_ElapsedTime = deltaTime;
//    }
//}
