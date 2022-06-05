#include "PointComponent.h"
#include <fstream>
#include <iostream>
#include <cassert>
#include "Renderer.h"
#include "GameObject.h"

PointComponent::PointComponent(const std::shared_ptr<dae::GameObject>& gameObject, int startingPoints, glm::vec3 startPos)
	:Component(gameObject)
	, m_StartingPoints(startingPoints)
	, m_CurrentPoints(startingPoints)
    , m_StartingPos(startPos)
{
    m_Transform = m_GameObject.lock()->GetComponent<dae::Transform>();
    m_Transform.lock()->SetPosition(startPos);
}

PointComponent::~PointComponent()
{
    SavePointsToFile();
}

void PointComponent::SavePointsToFile()
{
    std::ofstream highScores;
    highScores.open(m_HighScoresFile);
    highScores << std::to_string(m_CurrentPoints) << '\n';
    highScores.close();
}

void PointComponent::onNotify(const std::string& message)
{
    m_CurrentPoints += std::stoi(message);
    m_GameObject.lock()->GetComponent<dae::TextObject>()->SetText(std::to_string(m_CurrentPoints));
}

std::shared_ptr<dae::Component> PointComponent::Clone(const std::shared_ptr<dae::GameObject>& gameObject)
{
	return std::make_shared<PointComponent>(gameObject, m_StartingPoints, m_StartingPos);
}
