#include "CollisionComponent.h"
#include "utils.h"

CollisionComponent::CollisionComponent(std::shared_ptr<dae::GameObject> gameObject, Rectf shape)
	:Component(gameObject)
	, m_Shape(shape)
{}

void CollisionComponent::Update(float)
{

}

bool CollisionComponent::IsOverlapping(const Rectf& other) const
{
	return dae::utils::IsOverlapping(other, m_Shape);
}

std::shared_ptr<dae::Component> CollisionComponent::Clone(const std::shared_ptr<dae::GameObject>& gameObject)
{
	return std::make_shared<CollisionComponent>(gameObject, m_Shape);
}
