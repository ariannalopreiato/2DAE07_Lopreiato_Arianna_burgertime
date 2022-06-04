#pragma once
class State
{
public:
	State();
	virtual void OnLeaveState() = 0;
	virtual void OnEnterState() = 0;
	virtual void ChangeState(const std::shared_ptr<State>& newState) = 0;

private:
	std::weak_ptr<State> m_CurrentState;
};

