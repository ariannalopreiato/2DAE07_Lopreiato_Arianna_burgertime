#pragma once
#include "MiniginPCH.h"
#include "Command.h"

class MoveArrowUp : public dae::Command
{
public:
	MoveArrowUp() = default;
	void Execute() override;
};