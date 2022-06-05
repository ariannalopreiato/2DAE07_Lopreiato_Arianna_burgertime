#pragma once
#include "MiniginPCH.h"
#include "Command.h"

class SelectCommand : public dae::Command
{
public:
	SelectCommand() = default;
	void Execute() override;
};