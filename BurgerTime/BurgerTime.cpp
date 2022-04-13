#include <iostream>
#include "Minigin.h"
#include "Player.h"
#include "MoveCommand.h"
#include "CommandManager.h"
#include "ControllerButton.h"

int main(int, char* []) {
    dae::Minigin engine;
    engine.Run();
    auto pPlayerOne = std::make_shared<Player>(0);
    CommandManager commandManagerOne = CommandManager(pPlayerOne);
    commandManagerOne.SetMoveCommandsController(dae::ControllerButton::ButtonY, dae::ControllerButton::ButtonA, dae::ControllerButton::ButtonX, dae::ControllerButton::ButtonB);
    //auto pPlayerTwo = std::make_shared<Player>(1);
    return 0;
}
