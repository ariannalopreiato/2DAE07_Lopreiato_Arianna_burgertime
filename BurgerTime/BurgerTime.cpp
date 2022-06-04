#include <windows.h>
#include <iostream>
#include <chrono>
#include <thread>
#include "Minigin.h"
#include "SceneManager.h"
#include "FirstScene.h"
#include "SecondScene.h"
#include "ThirdScene.h"
#include "GameManager.h"

int main(int, char* []) {
    dae::Minigin engine;
    engine.Initialize();
    
    GameManager::SetGameMode(GameMode::multi);
    dae::SoundSystem* soundSystem = new dae::SDL_SoundSystem();
    dae::ServiceLocator::RegisterSoundSystem(soundSystem);
    dae::ServiceLocator::GetSoundSystem().loadSound("../Data/RandomCoinSound.wav");

    std::shared_ptr<FirstScene> firstScene = std::make_shared<FirstScene>("Level1");
    std::shared_ptr<SecondScene> secondScene = std::make_shared<SecondScene>("Level2");
    std::shared_ptr<ThirdScene> thirdScene = std::make_shared<ThirdScene>("Level3");

    auto& sceneManager = dae::SceneManager::GetInstance();
    sceneManager.AddScene(firstScene);
    sceneManager.AddScene(secondScene);
    sceneManager.AddScene(thirdScene);
    sceneManager.LoadScene("Level1");
    engine.Run();
    return 0;
}