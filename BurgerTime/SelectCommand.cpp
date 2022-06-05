#include "SelectCommand.h"
#include "SceneManager.h"
#include "MainMenuScene.h"

void SelectCommand::Execute()
{
	auto currentScene = dae::SceneManager::GetInstance().GetCurrentScene();
	currentScene->OnSelect();
}
