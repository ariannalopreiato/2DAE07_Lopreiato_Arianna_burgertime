#pragma once
#include "Component.h"
#include <string>

class PointComponent : public dae::Component
{
public:
	PointComponent(const std::shared_ptr<dae::GameObject>& gameObject, int startingPoints);
	void SavePointsToFile(const std::string& fileName);
	virtual std::shared_ptr<Component> Clone(const std::shared_ptr<dae::GameObject>& gameObject) override;
	int m_CurrentPoints{ 0 };

private:
	int m_StartingPoints{ 0 };
};

