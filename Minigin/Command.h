#pragma once
#include "GameObject.h"

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
}