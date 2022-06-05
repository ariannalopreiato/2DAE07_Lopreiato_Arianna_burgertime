#pragma once
#include "MiniginPCH.h"
#include "Command.h"

class MoveArrowDown : public dae::Command
{
public:
	MoveArrowDown() = default;
	void Execute() override;
};