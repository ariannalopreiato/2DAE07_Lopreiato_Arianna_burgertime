#include "CommandManager.h"
#include "InputManager.h"

CommandManager::CommandManager(const std::shared_ptr<Player>& player)
	: m_Player(player)
{
	//define movement commands
	m_MoveUp = std::make_unique<MoveCommand>(player, 0.0f, 1.0f);
	m_MoveDown = std::make_unique<MoveCommand>(player, 0.0f, -1.0f);
	m_MoveLeft = std::make_unique<MoveCommand>(player, -1.0f, 0.0f);
	m_MoveRight = std::make_unique<MoveCommand>(player, 1.0f, 0.0f);
}

void CommandManager::SetMoveCommandsController(dae::ControllerButton buttonUp, dae::ControllerButton buttonDown, dae::ControllerButton buttonLeft, dae::ControllerButton buttonRight)
{
	int playerIdx = m_Player.lock()->GetPlayerIdx();
	auto& input = dae::InputManager::GetInstance();
	input.AddCommandController(std::move(m_MoveUp), buttonUp, playerIdx);
	input.AddCommandController(std::move(m_MoveDown), buttonDown, playerIdx);
	input.AddCommandController(std::move(m_MoveLeft), buttonLeft, playerIdx);
	input.AddCommandController(std::move(m_MoveRight), buttonRight, playerIdx);
}
