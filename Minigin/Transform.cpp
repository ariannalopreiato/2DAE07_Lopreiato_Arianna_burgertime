#include "MiniginPCH.h"
#include "Transform.h"


dae::Transform::Transform(const std::shared_ptr<GameObject>& gameObject)
	:Component(gameObject) {}

void dae::Transform::SetPosition(const float x, const float y, const float z)
{
	m_Position.x = x;
	m_Position.y = y;
	m_Position.z = z;
}

dae::Component* dae::Transform::Clone(const std::shared_ptr<GameObject>& gameObject)
{
	return new Transform(gameObject);
}
