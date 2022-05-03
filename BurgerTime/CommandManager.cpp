#include "CommandManager.h"
#include "InputManager.h"

CommandManager::CommandManager()
{
	//define movement commands
	//float speed = player->GetSpeed();
	//m_MoveUp = std::make_unique<MoveCommand>(player, 0.0f, speed);
	//m_MoveDown = std::make_unique<MoveCommand>(player, 0.0f, -speed);
	//m_MoveLeft = std::make_unique<MoveCommand>(player, -speed, 0.0f);
	//m_MoveRight = std::make_unique<MoveCommand>(player, speed, 0.0f);
}

void CommandManager::SetMoveCommandsController(dae::ControllerButton , dae::ControllerButton , dae::ControllerButton , dae::ControllerButton )
{
	//int playerIdx = m_Player.lock()->GetPlayerIdx();
	//auto& input = dae::InputManager::GetInstance();
	//input.AddCommandController(std::move(m_MoveUp), buttonUp, playerIdx);
	//input.AddCommandController(std::move(m_MoveDown), buttonDown, playerIdx);
	//input.AddCommandController(std::move(m_MoveLeft), buttonLeft, playerIdx);
	//input.AddCommandController(std::move(m_MoveRight), buttonRight, playerIdx);
}

void CommandManager::SetAttackCommandController(dae::ControllerButton )
{
	//int playerIdx = m_Player.lock()->GetPlayerIdx();
	//auto& input = dae::InputManager::GetInstance();
	//input.AddCommandController(std::move(m_Attack), attack, playerIdx);
}
