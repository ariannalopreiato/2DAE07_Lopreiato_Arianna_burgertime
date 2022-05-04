#include <windows.h>
#include "InputComponent.h"
#include "InputManager.h"

InputComponent::InputComponent(const std::shared_ptr<dae::GameObject>& gameObject, int playerIdx)
	:Component(gameObject)
	, m_PlayerIdx(playerIdx)
{}

void InputComponent::AddCommand(std::unique_ptr<dae::Command> command, dae::ControllerButton button)
{
	auto& inputManager = dae::InputManager::GetInstance();
	inputManager.AddCommandController(std::move(command), button, m_PlayerIdx);
}

std::shared_ptr<dae::Component> InputComponent::Clone(const std::shared_ptr<dae::GameObject>& gameObject)
{
	return std::make_shared<InputComponent>(gameObject, m_PlayerIdx);
}
