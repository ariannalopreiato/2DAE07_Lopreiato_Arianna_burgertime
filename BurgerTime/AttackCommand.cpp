#include "AttackCommand.h"
#include "Player.h"

AttackCommand::AttackCommand(const std::shared_ptr<Player>& playerObject)
	: m_Player(playerObject)
{}

void AttackCommand::Execute()
{
	m_Player.lock()->ThrowPepper();
}