#pragma once
#include "MainMenuState.h"
#include "PlayingState.h"
#include "GameOverState.h"
#include "Singleton.h"

enum class GameState
{
	mainMenu, playing, gameOver
};

class GameStateHandler : public dae::Singleton<GameStateHandler>
{
public:
	void ChangeState(GameState newState);

private:
	MainMenuState m_MainMenuState{};
	PlayingState m_PlayingState{};
	GameOverState m_GameOverState{};

	dae::State* m_CurrentState{ nullptr };
};

