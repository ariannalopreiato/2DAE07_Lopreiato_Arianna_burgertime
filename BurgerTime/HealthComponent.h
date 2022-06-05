#pragma once
#include "MiniginPCH.h"
#include "Component.h"
#include "TextureComponent.h"
#include "Observer.h"

class HealthComponent : public dae::Component, public dae::Observer
{
public:
	HealthComponent(std::shared_ptr<dae::GameObject> gameObject, int lives);
	void Update(float elapsedTime);
	bool IsDead() const;
	int GetCurrentLives() const;
	void SpawnLife();
	void RemoveLife();
	virtual void onNotify(const std::string& message);
	virtual std::shared_ptr<Component> Clone(const std::shared_ptr<dae::GameObject>& gameObject) override;

private:
	int m_StartingLives{};
	int m_CurrentLives{};
	bool m_IsDead{ false };
	glm::vec3 m_TopMostPos{};
	int m_Distance{ 5 };
	float m_Size{ 20.f };

	std::vector<std::shared_ptr<dae::GameObject>> m_LivesDisplay{};
};

