#include <windows.h>
#include <iostream>
#include <chrono>
#include <thread>
#include "Minigin.h"
#include "SceneManager.h"
#include "FirstScene.h"
#include "SecondScene.h"
#include "ThirdScene.h"

int main(int, char* []) {
    dae::Minigin engine;
    engine.Initialize();
   // auto& scene = dae::SceneManager::GetInstance().CreateScene("Demo");

    std::shared_ptr<FirstScene> firstScene = std::make_shared<FirstScene>("Level 1");
    std::shared_ptr<SecondScene> secondScene = std::make_shared<SecondScene>("Level 2");
    std::shared_ptr<ThirdScene> thirdScene = std::make_shared<ThirdScene>("Level 3");
    //firstScene->LoadSceneElements();

    auto& sceneManager = dae::SceneManager::GetInstance();
    sceneManager.AddScene(firstScene);
    sceneManager.AddScene(secondScene);
    sceneManager.AddScene(thirdScene);
    sceneManager.LoadScene("Level 1");
    engine.Run();
    return 0;
}