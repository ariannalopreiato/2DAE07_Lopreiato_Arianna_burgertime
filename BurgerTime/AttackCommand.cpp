#include "AttackCommand.h"

AttackCommand::AttackCommand(std::shared_ptr<PlayerComponent> player)
	:m_Player(player)
{}

void AttackCommand::Execute()
{
	m_Player->Attack();
}