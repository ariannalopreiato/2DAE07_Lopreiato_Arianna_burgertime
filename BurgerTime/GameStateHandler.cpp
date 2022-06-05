#include "GameStateHandler.h"

void GameStateHandler::ChangeState(GameState newState)
{
	if (m_CurrentState != nullptr)
		m_CurrentState->OnLeaveState();

	switch (newState)
	{
	case GameState::mainMenu:
		m_CurrentState = &m_MainMenuState;
		break;
	case GameState::playing:
		m_CurrentState = &m_PlayingState;
		break;
	case GameState::gameOver:
		m_CurrentState = &m_GameOverState;
		break;
	}

	m_CurrentState->OnEnterState();

}
