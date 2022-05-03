#pragma once
#include "Component.h"

class InputComponent : public dae::Component
{
public:
	InputComponent(std::shared_ptr<dae::GameObject> gameObject, int playerIdx);
	void Update(float elapsedSec);
	void AddCommand(std::unique_ptr<dae::Command> command, dae::ControllerButton button);
	virtual std::shared_ptr<Component> Clone(const std::shared_ptr<dae::GameObject>& gameObject) override;

private:
	int m_PlayerIdx;
};

