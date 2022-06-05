#pragma once
#include "MiniginPCH.h"
#include "State.h"

class GameOverState : public dae::State
{
public:
	virtual void OnLeaveState();
	virtual void OnEnterState();
};

