#pragma once
#include "MoveCommand.h"
#include "AttackCommand.h"
#include "ControllerButton.h"

class CommandManager
{
public:
	CommandManager();
	void SetMoveCommandsController(dae::ControllerButton buttonUp, dae::ControllerButton buttonDown, dae::ControllerButton buttonLeft, dae::ControllerButton buttonRight);
	//void SetMoveCommandsKeyboard();
	void SetAttackCommandController(dae::ControllerButton attack);
	//void SetAttackCommandKeyboard();
private:
	std::unique_ptr<MoveCommand> m_MoveUp;
	std::unique_ptr<MoveCommand> m_MoveDown;
	std::unique_ptr<MoveCommand> m_MoveLeft;
	std::unique_ptr<MoveCommand> m_MoveRight;
	std::unique_ptr<AttackCommand> m_Attack;
};

