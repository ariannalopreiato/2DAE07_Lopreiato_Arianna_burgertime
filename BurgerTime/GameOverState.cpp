#include "GameOverState.h"
#include "SceneManager.h"
#include "InputManager.h"
#include "GameManager.h"
#include "GameOverScene.h"

void GameOverState::OnLeaveState()
{
	auto gameOverScene = std::static_pointer_cast<GameOverScene>(dae::SceneManager::GetInstance().GetSceneByName("GameOver"));
	gameOverScene->WriteToFile();

	dae::InputManager::GetInstance().CleanCommands();
	dae::SceneManager::GetInstance().DeleteScene("GameOver");
}

void GameOverState::OnEnterState()
{
	dae::SceneManager::GetInstance().LoadScene("GameOver");
}
