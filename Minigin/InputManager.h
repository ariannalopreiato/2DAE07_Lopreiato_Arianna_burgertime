#pragma once
#include "Singleton.h"
#include <vector>
#include <XInput.h>
#include <array>
#include "Command.h"
#include "ControllerButton.h"

namespace dae
{
	struct FullCommandController
	{
		FullCommandController(std::unique_ptr<Command> command, ControllerButton button, bool executeOnPress)
			:m_Command(std::move(command)), m_Button(button), m_ExecutePress(executeOnPress) {}

		std::unique_ptr<Command> m_Command;
		ControllerButton m_Button;
		bool m_ExecutePress;
	};

	struct FullCommandKeyboard
	{
		FullCommandKeyboard(std::unique_ptr<Command> command, SDL_Scancode button, bool executeOnPress)
			:m_Command(std::move(command)), m_Key(button), m_ExecutePress(executeOnPress) {}

		std::unique_ptr<Command> m_Command;
		SDL_Scancode m_Key;
		bool m_ExecutePress;
	};

	class InputManager final : public Singleton<InputManager>
	{
	public:
		~InputManager();
		bool ProcessInput();
		bool IsPressed(ControllerButton button, int playerIdx = 0) const;
		bool IsReleased(ControllerButton button, int playerIdx = 0) const;
		bool IsPressed(SDL_Scancode key, int playerIdx = 0) const;
		bool IsReleased(SDL_Scancode key, int playerIdx = 0) const;
		void AddCommandController(std::unique_ptr<Command> command, ControllerButton button, bool executeOnPress, int playerIdx = 0);
		void AddCommandKeyboard(std::unique_ptr<Command> command, SDL_Scancode key, bool executeOnPress);

	private:
		friend Singleton<InputManager>;
		InputManager();
		inline static constexpr int m_NrOfPlayers{ 2 }; //constant expression at compile time that cannot be changed, inline -> initialize static variable in the header
		inline static constexpr int m_NrOfKeys{ 122 };

		std::array<int, m_NrOfPlayers> m_Players{};
		std::array<int, m_NrOfPlayers> m_ButtonsPressedThisFrame{};
		std::array<int, m_NrOfPlayers> m_ButtonsReleasedThisFrame{};

		std::array<XINPUT_STATE, m_NrOfPlayers> m_CurrentStatesController{};
		std::array<XINPUT_STATE, m_NrOfPlayers> m_PreviousStatesController{};
		std::array<std::vector<std::unique_ptr<FullCommandController>>, m_NrOfPlayers> m_ControllerCommands{};

		std::array<bool, m_NrOfKeys> m_CurrentStatesKey{};
		std::array<bool, m_NrOfKeys> m_PreviousStatesKey{};
		std::vector<std::unique_ptr<FullCommandKeyboard>> m_KeyboardCommands{};
	};
}