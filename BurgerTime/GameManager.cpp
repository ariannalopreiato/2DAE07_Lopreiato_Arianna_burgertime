#include "GameManager.h"

GameManager::GameManager(GameMode gameMode)
	:m_GameMode(gameMode)
{}

void GameManager::InitializePlayer()
{
	if (m_GameMode == GameMode::single)
	{

	}
	else if (m_GameMode == GameMode::multi)
	{

	}
	else
	{

	}
}

void GameManager::InitializeUI()
{
}
