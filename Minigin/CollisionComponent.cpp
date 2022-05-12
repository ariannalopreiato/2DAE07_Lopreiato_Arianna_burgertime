#include "MiniginPCH.h"
#include "CollisionComponent.h"
#include "utils.h"
#include "GameObject.h"

dae::CollisionComponent::CollisionComponent(std::shared_ptr<dae::GameObject> gameObject)
	:Component(gameObject)
{
	m_Transform = gameObject->GetComponent<Transform>();
}

void dae::CollisionComponent::Update(float)
{
	auto currentGameObjectPos = m_Transform.lock()->GetPosition();
	m_Shape.left = currentGameObjectPos.x;
	m_Shape.bottom = currentGameObjectPos.y;
	auto currentGameObjectSize = m_Transform.lock()->GetSize();
	m_Shape.width = currentGameObjectSize.x;
	m_Shape.height = currentGameObjectSize.y;
}

bool dae::CollisionComponent::IsOverlapping(const Rectf& other) const
{
	return dae::utils::IsOverlapping(other, m_Shape);
}

const Rectf& dae::CollisionComponent::GetCollisionBox() const
{
	return m_Shape;
}

std::shared_ptr<dae::Component> dae::CollisionComponent::Clone(const std::shared_ptr<dae::GameObject>& gameObject)
{
	return std::make_shared<CollisionComponent>(gameObject);
}