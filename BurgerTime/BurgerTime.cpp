#include <windows.h>
#include <iostream>
#include <chrono>
#include <thread>
#include "Minigin.h"
#include "SceneManager.h"
#include "FirstScene.h"
#include "SecondScene.h"
#include "ThirdScene.h"
#include "GameOverScene.h"
#include "MainMenuScene.h"
#include "GameManager.h"
#include "GameStateHandler.h"

int main(int, char* []) {
    dae::Minigin engine;
    engine.Initialize();

    dae::InputManager::GetInstance().ProcessInput(); //call to check controller status (update default values)
    auto controllers = dae::InputManager::GetInstance().GetConnectedControllers();

    if(controllers[0] && controllers[1])
        GameManager::InputSetup(InputMethod::controller, InputMethod::controller);
    else if(controllers[0])
        GameManager::InputSetup(InputMethod::controller, InputMethod::keyboard);
    else
        GameManager::InputSetup(InputMethod::keyboard, InputMethod::keyboard);

    dae::SoundSystem* soundSystem = new dae::SDL_SoundSystem();
    dae::ServiceLocator::RegisterSoundSystem(soundSystem);
    dae::ServiceLocator::GetSoundSystem().loadSound("../Data/Sounds/ingredientDrop.mp3");
    dae::ServiceLocator::GetSoundSystem().loadMusic("../Data/Sounds/background.wav");

    std::shared_ptr<MainMenuScene> mainMenuScene = std::make_shared<MainMenuScene>("MainMenu");
    std::shared_ptr<FirstScene> firstScene = std::make_shared<FirstScene>("Level1");
    std::shared_ptr<SecondScene> secondScene = std::make_shared<SecondScene>("Level2");
    std::shared_ptr<ThirdScene> thirdScene = std::make_shared<ThirdScene>("Level3");
    std::shared_ptr<GameOverScene> gameOverScene = std::make_shared<GameOverScene>("GameOver");

    auto& sceneManager = dae::SceneManager::GetInstance();
    sceneManager.AddScene(mainMenuScene);
    sceneManager.AddScene(firstScene);
    sceneManager.AddScene(secondScene);
    sceneManager.AddScene(thirdScene);
    sceneManager.AddScene(gameOverScene);
   
    GameStateHandler::GetInstance().ChangeState(GameState::mainMenu);

    engine.Run();
    return 0;
}