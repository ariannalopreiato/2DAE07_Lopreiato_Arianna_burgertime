#include "MiniginPCH.h"
#include "Transform.h"


dae::Transform::Transform(const std::shared_ptr<GameObject>& gameObject)
	:Component(gameObject) {}

void dae::Transform::SetPosition(const Point2f& pos)
{
	SetPosition(pos.x, pos.y, 0.0f);
}

void dae::Transform::SetSize(float width, float height, float depth)
{
	m_Size.x = width;
	m_Size.y = height;
	m_Size.z = depth;
}

void dae::Transform::Scale(float scaleX, float scaleY, float scaleZ)
{
	m_Size.x *= scaleX;
	m_Size.y *= scaleY;
	m_Size.z *= scaleZ;
}

void dae::Transform::SetPosition(const float x, const float y, const float z)
{
	m_Position.x = x;
	m_Position.y = y;
	m_Position.z = z;
}

std::shared_ptr<dae::Component> dae::Transform::Clone(const std::shared_ptr<GameObject>& gameObject)
{
	return std::make_shared<Transform>(gameObject);
}
