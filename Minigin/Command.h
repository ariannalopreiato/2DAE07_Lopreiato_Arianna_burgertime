#pragma once
#include "GameObject.h"
#include "Player.h"

namespace dae
{
	class Command
	{
	public:
		Command() {};
		virtual void Execute() = 0;
		virtual ~Command() = default;
		//SDL_KeyCode GetKey();

	private:
		//SDL_Keycode m_Key;
	};

	class MoveCommand : public Command
	{
	private:
		MoveCommand(Player* playerObject, float x, float y)
			: m_Player(playerObject), m_X(x) , m_Y(y) {}

		void Execute()
		{
			m_Player->Move(m_X, m_Y);
		}

		~MoveCommand()
		{
			m_Player = nullptr;
			delete m_Player;
		}

	public:
		float m_X;
		float m_Y;
		Player* m_Player;
	};
}