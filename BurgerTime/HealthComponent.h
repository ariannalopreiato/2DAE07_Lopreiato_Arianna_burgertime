#pragma once
#include "MiniginPCH.h"
#include "Component.h"
#include "TextureComponent.h"

class HealthComponent : public dae::Component
{
public:
	HealthComponent(std::shared_ptr<dae::GameObject> gameObject, int lives, const glm::vec3& pos = glm::vec3{0.0f, 0.0f, 0.0f});
	void Update(float elapsedTime);
	bool IsDead() const;
	int GetCurrentLives() const;
	void SpawnLife();
	void RemoveLife();
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

