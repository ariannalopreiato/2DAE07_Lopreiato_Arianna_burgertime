#include "MiniginPCH.h"
#include "CollisionComponent.h"
#include "utils.h"

dae::CollisionComponent::CollisionComponent(std::shared_ptr<dae::GameObject> gameObject, Rectf shape)
	:Component(gameObject)
	, m_Shape(shape)
{}

bool dae::CollisionComponent::IsOverlapping(const Rectf& other) const
{
	return dae::utils::IsOverlapping(other, m_Shape);
}

std::shared_ptr<dae::Component> dae::CollisionComponent::Clone(const std::shared_ptr<dae::GameObject>& gameObject)
{
	return std::make_shared<CollisionComponent>(gameObject, m_Shape);
}
