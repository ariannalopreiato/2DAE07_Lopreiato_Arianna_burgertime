#include "MoveArrowUp.h"
#include "SceneManager.h"
#include "MainMenuScene.h"

void MoveArrowUp::Execute()
{
	auto currentScene = dae::SceneManager::GetInstance().GetCurrentScene();
	if (std::shared_ptr<MainMenuScene> scene{ std::dynamic_pointer_cast<MainMenuScene>(currentScene) })
		scene->DecreaseSelectedMode();
}
