#pragma once
#include "MiniginPCH.h"
#include "Component.h"
#include "Pepper.h"
#include "Texture2D.h"
#include "CollisionComponent.h"
#include "TextureComponent.h"
#include "AnimationComponent.h"
#include "Subject.h"

class PlayerAttackComponent : public dae::Component, public dae::Subject
{
public:
	PlayerAttackComponent(const std::shared_ptr<dae::GameObject>& gameObject, int pepperShots);
	void Update(float elapsedSec);
	void Attack();
	int GetPepperShots() const;
	virtual std::shared_ptr<Component> Clone(const std::shared_ptr<dae::GameObject>& gameObject) override;

private:
	void SpawnPepper();

	int m_PepperShots{ 0 };
	int m_CurrentShots{ 0 };
	float m_SpawnTime{ 3.f };
	float m_CurrentTime{ 0.0f };
	bool m_IsPepperInitialized{ false };
	std::weak_ptr<dae::GameObject> m_Pepper;
};

