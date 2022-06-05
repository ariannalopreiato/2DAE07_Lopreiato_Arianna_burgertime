#include "PlayingState.h"
#include "SceneManager.h"
#include "InputManager.h"
#include "LevelCreator.h"
#include "EnemyManager.h"
#include "GameManager.h"
#include "GameOverScene.h"

void PlayingState::OnLeaveState()
{
	auto gameOverScene = std::static_pointer_cast<GameOverScene>(dae::SceneManager::GetInstance().GetSceneByName("GameOver"));
	auto points = GameManager::GetScoreComponent()->m_CurrentPoints;
	gameOverScene->SetPoints(points);
	
	dae::InputManager::GetInstance().CleanCommands();
	LevelCreator::CleanLevel();
	EnemyManager::CleanEnemies();
	auto currentScene = dae::SceneManager::GetInstance().GetCurrentSceneName();
	dae::SceneManager::GetInstance().DeleteScene(currentScene);
}

void PlayingState::OnEnterState()
{
	GameManager::LoadUI();
	dae::SceneManager::GetInstance().LoadScene("Level1");
}
