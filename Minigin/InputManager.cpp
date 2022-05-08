#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <XInput.h>
#pragma comment(lib, "xinput.lib")
#include "MiniginPCH.h"
#include "InputManager.h"
#include "GameObject.h"

dae::InputManager::InputManager()
{
	for (int i = 0; i < m_NrOfPlayers; ++i)
	{
		m_Players[i] = i;
	}
}

dae::InputManager::~InputManager()
{}

bool dae::InputManager::ProcessInput()
{
	for (int i = 0; i < m_NrOfPlayers; ++i)
	{
		ZeroMemory(&m_PreviousStates[i], sizeof(XINPUT_STATE));
		m_PreviousStates[i] = m_CurrentStates[i];
		XInputGetState(i, &m_CurrentStates[i]);
		auto buttonChanges = m_CurrentStates[i].Gamepad.wButtons ^ m_PreviousStates[i].Gamepad.wButtons;
		m_ButtonsPressedThisFrame[i] = buttonChanges & m_CurrentStates[i].Gamepad.wButtons;
		m_ButtonsReleasedThisFrame[i] = buttonChanges & (~m_CurrentStates[i].Gamepad.wButtons);
	}

	SDL_Event e;
	bool isRunning{ true };
	while (SDL_PollEvent(&e)) {
		if (e.type == SDL_QUIT) {
			isRunning = false;
		}
		//if (e.type == SDL_KEYDOWN) {
		//	
		//}
		//if (e.type == SDL_MOUSEBUTTONDOWN) {
		//}
	}

	for (int j = 0; j < m_NrOfPlayers; ++j)
	{
		for (size_t k = 0; k < m_ControllerCommands[j].size(); ++k)
		{
			if (m_ControllerCommands[j][k]->m_ExecutePress)
			{
				if (IsPressed(m_ControllerCommands[j][k]->m_Button, j))
					m_ControllerCommands[j][k]->m_Command->Execute();
			}
			else
			{
				if (IsReleased(m_ControllerCommands[j][k]->m_Button, j))
					m_ControllerCommands[j][k]->m_Command->Execute();
			}
		}
	}
	return isRunning;
}

bool dae::InputManager::IsPressed(ControllerButton button, int playerIdx) const
{
	//if current state is pressed and previous state is released
	return ((m_CurrentStates[playerIdx].Gamepad.wButtons & (unsigned)button) != 0);
}

bool dae::InputManager::IsReleased(ControllerButton button, int playerIdx) const
{
	//if current state is released and previous state is pressed
	return ((m_CurrentStates[playerIdx].Gamepad.wButtons & (unsigned)button) == 0 && (m_PreviousStates[playerIdx].Gamepad.wButtons & (unsigned)button) != 0);
}

//bool dae::InputManager::IsPressed(SDL_KeyCode key) const
//{
//	return ((m_CurrentState.Gamepad.wButtons & (unsigned)key) != 0 && (m_PreviousState.Gamepad.wButtons & (unsigned)key) == 0);
//}
//
//bool dae::InputManager::IsReleased(SDL_KeyCode key) const
//{
//	return ((m_CurrentState.Gamepad.wButtons & (unsigned)key) == 0 && (m_PreviousState.Gamepad.wButtons & (unsigned)key) != 0);
//}

void dae::InputManager::AddCommandController(std::unique_ptr<Command> command, ControllerButton button, bool executeOnPress, int playerIdx)
{
	//push_back copies by default, emplace_back creates object at the back -> unique ptr cannot be copied
	//but compiler is smart enough to use the move overload of push_back
	m_ControllerCommands[playerIdx].push_back(std::make_unique<FullCommand>(std::move(command), button, executeOnPress));
}