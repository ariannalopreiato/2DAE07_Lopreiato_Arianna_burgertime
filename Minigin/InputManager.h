#pragma once
#include "Singleton.h"
#include <vector>
#include "Command.h"
#include <XInput.h>
#include <array>

namespace dae
{
	enum class ControllerButton
	{
		ButtonA = XINPUT_GAMEPAD_A,
		ButtonB = XINPUT_GAMEPAD_B,
		ButtonX = XINPUT_GAMEPAD_X,
		ButtonY = XINPUT_GAMEPAD_Y
	};

	struct FullCommand
	{
		FullCommand(std::unique_ptr<Command> command, ControllerButton button)
			:m_Command(std::move(command)), m_Button(button) {}

		std::unique_ptr<Command> m_Command;
		ControllerButton m_Button;
	};

	class InputManager final : public Singleton<InputManager>
	{
	public:
		~InputManager();
		bool ProcessInput();
		bool IsPressed(ControllerButton button, int playerIdx = 0) const;
		bool IsReleased(ControllerButton button, int playerIdx = 0) const;
		//bool IsPressed(SDL_KeyCode key) const;
		//bool IsReleased(SDL_KeyCode key) const;
		void AddCommandController(std::unique_ptr<Command> command, ControllerButton button, int playerIdx = 0);
		//void SetCommandKeyboard(Command*& command, SDL_KeyCode key);

	private:
		friend Singleton<InputManager>;
		InputManager();
		inline static constexpr int m_NrOfPlayers{ 2 }; //constant expression at compile time that cannot be changed, inline -> initialize static variable in the header
		std::array<int, m_NrOfPlayers> m_Players;
		std::array<int, m_NrOfPlayers> m_ButtonsPressedThisFrame;
		std::array<int, m_NrOfPlayers> m_ButtonsReleasedThisFrame;
		std::array<XINPUT_STATE, m_NrOfPlayers> m_CurrentStates;
		std::array<XINPUT_STATE, m_NrOfPlayers> m_PreviousStates;
		std::array<std::vector<std::unique_ptr<FullCommand>>, m_NrOfPlayers> m_ControllerCommands;
	};
}