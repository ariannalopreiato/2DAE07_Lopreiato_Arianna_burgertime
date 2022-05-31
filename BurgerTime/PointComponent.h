#pragma once
#include "MiniginPCH.h"
#include "Component.h"
#include <string>
#include "Observer.h"
#include "TextObject.h"

class PointComponent : public dae::Component, public dae::Observer
{
public:
	PointComponent(const std::shared_ptr<dae::GameObject>& gameObject, int startingPoints, glm::vec3 startPos);
	void SavePointsToFile(const std::string& fileName);
	virtual void onNotify(const std::string& message);
	virtual std::shared_ptr<Component> Clone(const std::shared_ptr<dae::GameObject>& gameObject) override;
	int m_CurrentPoints{ 0 };

private:
	int m_StartingPoints{ 0 };
	glm::vec3 m_StartingPos{};
	std::weak_ptr<dae::Transform> m_Transform;
};

