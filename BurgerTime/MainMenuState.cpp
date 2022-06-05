#include "MainMenuState.h"
#include "SceneManager.h"
#include "InputManager.h"

void MainMenuState::OnLeaveState()
{
	dae::InputManager::GetInstance().CleanCommands();
	dae::SceneManager::GetInstance().DeleteScene("MainMenu");
}

void MainMenuState::OnEnterState()
{
	dae::SceneManager::GetInstance().LoadScene("MainMenu");
}
