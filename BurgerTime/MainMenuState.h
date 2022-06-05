#pragma once
#include "MiniginPCH.h"
#include "State.h"

class MainMenuState : public dae::State
{
public:
	virtual void OnLeaveState();
	virtual void OnEnterState();
};