#pragma once
#include "MiniginPCH.h"
#include "Component.h"
#include "Command.h"
#include "ControllerButton.h"

class InputComponent : public dae::Component
{
public:
	InputComponent(const std::shared_ptr<dae::GameObject>& gameObject, int playerIdx);
	void AddCommand(std::unique_ptr<dae::Command> command, dae::ControllerButton button);
	virtual std::shared_ptr<Component> Clone(const std::shared_ptr<dae::GameObject>& gameObject) override;

private:
	int m_PlayerIdx;
};

