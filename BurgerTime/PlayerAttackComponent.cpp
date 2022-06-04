#include "PlayerAttackComponent.h"
#include "GameObject.h"
#include "Renderer.h"
#include <iostream>
#include "PlayerComponent.h"

PlayerAttackComponent::PlayerAttackComponent(const std::shared_ptr<dae::GameObject>& gameObject, int pepperShots)
	:Component(gameObject)
	, m_PepperShots(pepperShots)
	, m_CurrentShots(pepperShots)
{}

void PlayerAttackComponent::Update(float elapsedSec)
{
	if (m_IsPepperInitialized)
	{
		m_CurrentTime += elapsedSec;
		if (m_CurrentTime >= m_SpawnTime)
		{
			m_IsPepperInitialized = false;
			m_GameObject.lock()->RemoveChildAt(0);
			//m_Pepper.lock()->m_MarkForDestruction = true;
		}
	}
}

void PlayerAttackComponent::Attack()
{
	if (m_CurrentShots > 0 && !m_IsPepperInitialized)
	{
		--m_CurrentShots;
		SpawnPepper();
		m_IsPepperInitialized = true;
	}
}

void PlayerAttackComponent::SpawnPepper()
{
	auto gameObj  = std::make_shared<dae::GameObject>();

	auto picture = dae::ResourceManager::GetInstance().LoadTexture("../Data/Sprites/pepper.png");
	auto texture = std::make_shared<dae::TextureComponent>(gameObj, picture);

	auto pepper = std::make_shared<Pepper>(gameObj, m_GameObject.lock());

	auto collision = std::make_shared<dae::CollisionComponent>(gameObj);
	//auto animation = std::make_shared<dae::AnimationComponent>(gameObj, ); //todo

	gameObj->AddComponent(pepper);
	gameObj->AddComponent(texture);
	gameObj->AddComponent(collision);
	//pepper->AddComponent(animation);
	m_Pepper = gameObj;
	m_GameObject.lock()->AddChild(m_Pepper.lock());
}

int PlayerAttackComponent::GetPepperShots() const
{
	return m_CurrentShots;
}

std::shared_ptr<dae::Component> PlayerAttackComponent::Clone(const std::shared_ptr<dae::GameObject>& gameObject)
{
	return std::make_shared<PlayerAttackComponent>(gameObject, m_PepperShots);
}
