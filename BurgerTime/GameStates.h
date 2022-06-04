#pragma once
#include "MiniginPCH.h"
#include "State.h"

enum class GameState
{
	mainMenu, playing, highScores
};

class GameStates : public State
{
public:
	virtual void OnLeaveState();
	virtual void OnEnterState();
	virtual void ChangeState(const std::shared_ptr<State>& newState);

private:
	GameState m_CurrentState{ GameState::mainMenu };
};

