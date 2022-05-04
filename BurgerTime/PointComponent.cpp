#include "PointComponent.h"

PointComponent::PointComponent(const std::shared_ptr<dae::GameObject>& gameObject, int startingPoints)
	:Component(gameObject)
	, m_StartingPoints(startingPoints)
	, m_CurrentPoints(startingPoints)
{}

std::shared_ptr<dae::Component> PointComponent::Clone(const std::shared_ptr<dae::GameObject>& gameObject)
{
	return std::make_shared<PointComponent>(gameObject, m_StartingPoints);
}
