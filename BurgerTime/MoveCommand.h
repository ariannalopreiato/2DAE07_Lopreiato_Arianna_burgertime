#pragma once
#include "MiniginPCH.h"
#include <memory>
#include "Command.h"
#include "Vector2f.h"

class Player;
class MoveCommand : public dae::Command
{
public:
	//pass the object to move and in which direction to move it
	MoveCommand();
	void Execute() override;
};