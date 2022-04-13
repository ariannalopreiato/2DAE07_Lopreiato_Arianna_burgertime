#include "MoveCommand.h"
#include "Player.h"

MoveCommand::MoveCommand(const std::shared_ptr<Player>& playerObject, float x, float y)
	: m_Player(playerObject), m_X(x), m_Y(y) {}

void MoveCommand::Execute()
{
	m_Player.lock()->Move(m_X, m_Y);
}