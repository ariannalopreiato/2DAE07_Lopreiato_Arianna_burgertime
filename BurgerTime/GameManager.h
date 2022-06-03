#pragma once
#include "MiniginPCH.h"
#include "SceneManager.h"

enum class GameMode
{
	single, multi, versus
};

class GameManager
{
public:
	GameManager(GameMode gameMode);
	//void LevelComplete();

private:
	GameMode m_GameMode;
	void InitializePlayer();
	void InitializeUI();
};
