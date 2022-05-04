#pragma once
#include "MiniginPCH.h"
#include <memory>
#include "Command.h"
#include "PlayerComponent.h"

class MoveCommand : public dae::Command
{
public:
	MoveCommand(std::shared_ptr<PlayerComponent> player);
	void Execute() override;

private:
	std::shared_ptr<PlayerComponent> m_Player;
};