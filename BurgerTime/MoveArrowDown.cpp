#include "MoveArrowDown.h"
#include "SceneManager.h"
#include "MainMenuScene.h"

void MoveArrowDown::Execute()
{
	auto currentScene = dae::SceneManager::GetInstance().GetCurrentScene();
	if (std::shared_ptr<MainMenuScene> scene{ std::dynamic_pointer_cast<MainMenuScene>(currentScene) })
		scene->IncreaseSelectedMode();
}
