#pragma once
#include "MoveCommand.h"
#include "Player.h"
#include "ControllerButton.h"

class CommandManager
{
public:
	CommandManager(const std::shared_ptr<Player>& player);
	void SetMoveCommandsController(dae::ControllerButton buttonUp, dae::ControllerButton buttonDown, dae::ControllerButton buttonLeft, dae::ControllerButton buttonRight);
	//void SetMoveCommandsKeyboard();

private:
	std::weak_ptr<Player> m_Player;
	std::unique_ptr<MoveCommand> m_MoveUp;
	std::unique_ptr<MoveCommand> m_MoveDown;
	std::unique_ptr<MoveCommand> m_MoveLeft;
	std::unique_ptr<MoveCommand> m_MoveRight;
};

