#include "Pepper.h"
#include "GameObject.h"
#include "Renderer.h"
#include "PlayerComponent.h"

Pepper::Pepper(const std::shared_ptr<dae::GameObject>& gameObject, const std::shared_ptr<dae::GameObject>& player)
	:Component(gameObject)
	, m_IsActive(false)
	, m_Player(player)
{
	m_Transform = m_GameObject.lock()->GetComponent<dae::Transform>();
	m_Transform.lock()->SetSize(m_SpriteSize, m_SpriteSize, 0.0f);
}

void Pepper::Update(float)
{
	m_PlayerPos = m_Player.lock()->GetComponent<dae::Transform>()->GetPosition();
	if (m_IsActive)
	{
		auto velocity = m_Player.lock()->GetComponent<PlayerComponent>()->GetVelocity();
		if (velocity.y == 0.0f)
		{
			if (velocity.x > 0.0f)
				m_Transform.lock()->SetPosition(m_PlayerPos.x + m_SpriteSize, m_PlayerPos.y, 0.0f);
			else
				m_Transform.lock()->SetPosition(m_PlayerPos.x - m_SpriteSize, m_PlayerPos.y, 0.0f);
		}
		else
		{
			if(velocity.y > 0.0f)
				m_Transform.lock()->SetPosition(m_PlayerPos.x, m_PlayerPos.y + m_SpriteSize, 0.0f);
			else
				m_Transform.lock()->SetPosition(m_PlayerPos.x, m_PlayerPos.y - m_SpriteSize  , 0.0f);
		}
		m_Animation.lock()->m_CanAnimate = true;
		m_Texture.lock()->m_IsImageShowing = true;
	}
	else
	{
		m_Animation.lock()->m_CanAnimate = false;
		m_Texture.lock()->m_IsImageShowing = false;
	}
}

void Pepper::ActivatePepper()
{
	m_IsActive = true;
}

std::shared_ptr<dae::Component> Pepper::Clone(const std::shared_ptr<dae::GameObject>& gameObject)
{
	return std::make_shared<Pepper>(gameObject, m_Player.lock());
}
