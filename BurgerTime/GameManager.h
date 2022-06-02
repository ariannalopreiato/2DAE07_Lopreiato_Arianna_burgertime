#pragma once
#include "MiniginPCH.h"

enum class GameMode
{
	single, multi, versus
};

class GameManager
{
public:
	GameManager(GameMode gameMode);

private:
	GameMode m_GameMode;
	void InitializePlayer();
	void InitializeUI();
};

