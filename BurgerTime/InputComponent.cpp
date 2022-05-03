#include "InputComponent.h"
#include "InputManager.h"

InputComponent::InputComponent(std::shared_ptr<dae::GameObject> gameObject, int playerIdx)
	:Component(gameObject)
	, m_PlayerIdx(playerIdx)
{}

void InputComponent::Update(float elapsedSec)
{
}

void InputComponent::AddCommand(std::unique_ptr<dae::Command> command, dae::ControllerButton button)
{
	auto& input = dae::InputManager::GetInstance();
	input.AddCommandController(std::move(command), button, m_PlayerIdx);
}

std::shared_ptr<dae::Component> InputComponent::Clone(const std::shared_ptr<dae::GameObject>& gameObject)
{
	return std::make_shared<InputComponent>(gameObject, m_PlayerIdx);
}
