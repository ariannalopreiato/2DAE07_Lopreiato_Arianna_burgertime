#include "MoveCommand.h"
#include "PlayerComponent.h"

MoveCommand::MoveCommand(std::shared_ptr<PlayerComponent> player, PlayerDirection direction)
	:m_Player(player)
	, m_Direction(direction)
{}

void MoveCommand::Execute()
{
	m_Player->Move(m_Direction);
}