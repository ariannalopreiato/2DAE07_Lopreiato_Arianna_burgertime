#pragma once
#include "MiniginPCH.h"
#include <memory>
#include "Command.h"

enum class PlayerDirection
{
	up, down, left, right
};

class PlayerComponent;
class MoveCommand : public dae::Command
{
public:
	MoveCommand(std::shared_ptr<PlayerComponent> player, PlayerDirection direction);
	void Execute() override;

private:
	std::shared_ptr<PlayerComponent> m_Player;
	PlayerDirection m_Direction;
};