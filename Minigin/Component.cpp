#include "MiniginPCH.h"
#include "Component.h"

dae::Component::Component(const std::shared_ptr<GameObject>& gameObject)
	:m_GameObject(gameObject) {}

void dae::Component::SetOwner(const std::shared_ptr<GameObject>& gameObject)
{
	m_GameObject = gameObject;
}
