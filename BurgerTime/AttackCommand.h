#pragma once
#include "MiniginPCH.h"
#include <memory>
#include "Command.h"

class Player;
class AttackCommand : public dae::Command
{
public:
	//pass the object to move and in which direction to move it
	AttackCommand(const std::shared_ptr<Player>& playerObject);
	void Execute() override;

private:
	float m_X;
	float m_Y;
	std::weak_ptr<Player> m_Player;
};