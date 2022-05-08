#pragma once
#include "GameObject.h"

namespace dae
{
	class Command
	{
	public:
		Command(){};
		virtual void Execute() = 0;
		virtual ~Command() = default;
	};
}