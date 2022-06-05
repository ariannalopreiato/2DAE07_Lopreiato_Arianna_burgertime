#pragma once
namespace dae
{
	class State
	{
	public:
		virtual void OnLeaveState() = 0;
		virtual void OnEnterState() = 0;
	};
}