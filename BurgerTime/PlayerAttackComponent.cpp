#include "PlayerAttackComponent.h"
#include "GameObject.h"
#include "Renderer.h"
#include <iostream>
#include "PlayerComponent.h"

PlayerAttackComponent::PlayerAttackComponent(const std::shared_ptr<dae::GameObject>& gameObject, int pepperShots)
	:Component(gameObject)
	, m_PepperShots(pepperShots)
	, m_CurrentShots(pepperShots)
{
	m_Pepper = SpawnPepper();
}

void PlayerAttackComponent::Update(float)
{
}

void PlayerAttackComponent::Attack()
{
	if (m_CurrentShots > 0)
	{
		--m_CurrentShots;
		m_IsActive = true;

		//m_Pepper.lock()->GetComponent<Pepper>()->ActivatePepper();
	}
}

std::shared_ptr<dae::GameObject> PlayerAttackComponent::SpawnPepper()
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

	return gameObj;
}

int PlayerAttackComponent::GetPepperShots() const
{
	return m_CurrentShots;
}

std::shared_ptr<dae::Component> PlayerAttackComponent::Clone(const std::shared_ptr<dae::GameObject>& gameObject)
{
	return std::make_shared<PlayerAttackComponent>(gameObject, m_PepperShots);
}
