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

    //GameManager::InputSetup(InputMethod::controller, InputMethod::keyboard);

    dae::SoundSystem* soundSystem = new dae::SDL_SoundSystem();
    dae::ServiceLocator::RegisterSoundSystem(soundSystem);
    dae::ServiceLocator::GetSoundSystem().loadSound("../Data/Sounds/ingredientDrop.mp3");
    dae::ServiceLocator::GetSoundSystem().loadMusic("../Data/Sounds/background.wav");
    dae::ServiceLocator::GetSoundSystem().loadSound("../Data/Sounds/start.mp3");

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