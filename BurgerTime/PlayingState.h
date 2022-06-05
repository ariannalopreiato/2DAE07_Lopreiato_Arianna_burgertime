#pragma once
#include "MiniginPCH.h"
#include "State.h"

class PlayingState : public dae::State
{
public:
	virtual void OnLeaveState();
	virtual void OnEnterState();
};

