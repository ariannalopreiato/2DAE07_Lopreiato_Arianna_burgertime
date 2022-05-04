#include "MoveCommand.h"

MoveCommand::MoveCommand(std::shared_ptr<PlayerComponent> player)
	:m_Player(player)
{}

void MoveCommand::Execute()
{
	m_Player->Move();
}