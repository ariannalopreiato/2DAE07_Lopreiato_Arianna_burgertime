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
		ZeroMemory(&m_PreviousStatesController[i], sizeof(XINPUT_STATE));
		m_PreviousStatesController[i] = m_CurrentStatesController[i];
		m_ConnectedControllers[i] = XInputGetState(i, &m_CurrentStatesController[i]) == ERROR_SUCCESS; //if it returns succes, controller is plugged in
		auto buttonChanges = m_CurrentStatesController[i].Gamepad.wButtons ^ m_PreviousStatesController[i].Gamepad.wButtons;
		m_ButtonsPressedThisFrame[i] = buttonChanges & m_CurrentStatesController[i].Gamepad.wButtons;
		m_ButtonsReleasedThisFrame[i] = buttonChanges & (~m_CurrentStatesController[i].Gamepad.wButtons);
	}

	m_PreviousStatesKey = m_CurrentStatesKey;

	SDL_Event e;
	bool isRunning{ true };
	while (SDL_PollEvent(&e)) {
		if (e.type == SDL_QUIT) {
			isRunning = false;
		}
	}

	for (int player = 0; player < m_NrOfPlayers; ++player)
	{
		for (size_t controller = 0; controller < m_ControllerCommands[player].size(); ++controller)
		{
			if (m_ControllerCommands[player][controller]->m_ExecutePress)
			{
				if (IsPressed(m_ControllerCommands[player][controller]->m_Button, player))
					m_ControllerCommands[player][controller]->m_Command->Execute();
			}
			else
			{
				if (IsReleased(m_ControllerCommands[player][controller]->m_Button, player))
					m_ControllerCommands[player][controller]->m_Command->Execute();
			}
		}
	}
	for (size_t key = 0; key < m_KeyboardCommands.size(); ++key)
	{
		SDL_Scancode currentKey = m_KeyboardCommands[key]->m_Key;
		if (SDL_GetKeyboardState(nullptr)[currentKey])
			m_KeyboardCommands[key]->m_Command->Execute();
	}
	return isRunning;
}

bool dae::InputManager::IsPressed(ControllerButton button, int playerIdx) const
{
	//if current state is pressed and previous state is released
	return ((m_CurrentStatesController[playerIdx].Gamepad.wButtons & (unsigned)button) != 0);
}

bool dae::InputManager::IsReleased(ControllerButton button, int playerIdx) const
{
	//if current state is released and previous state is pressed
	return ((m_CurrentStatesController[playerIdx].Gamepad.wButtons & (unsigned)button) == 0 && (m_PreviousStatesController[playerIdx].Gamepad.wButtons & (unsigned)button) != 0);
}

void dae::InputManager::AddCommandController(std::unique_ptr<Command> command, ControllerButton button, bool executeOnPress, int playerIdx)
{
	//emplace_back copies by default, emplace_back creates object at the back -> unique ptr cannot be copied
	//but compiler is smart enough to use the move overload of emplace_back
	m_ControllerCommands[playerIdx].emplace_back(std::make_unique<FullCommandController>(std::move(command), button, executeOnPress));
}

void dae::InputManager::AddCommandKeyboard(std::unique_ptr<Command> command, SDL_Scancode key, bool executeOnPress)
{
	m_KeyboardCommands.emplace_back(std::make_unique<FullCommandKeyboard>(std::move(command), key, executeOnPress));
}

const std::array<bool, dae::InputManager::m_NrOfPlayers>& dae::InputManager::GetConnectedControllers()
{
	return m_ConnectedControllers;
}

void dae::InputManager::CleanCommands()
{
	m_KeyboardCommands.clear();
	for (size_t i = 0; i < m_NrOfPlayers; ++i)
	{
		m_ControllerCommands[i].clear();
	}
}
