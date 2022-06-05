#include "HealthComponent.h"
#include "GameObject.h"

HealthComponent::HealthComponent(std::shared_ptr<dae::GameObject> gameObject, int lives)
	:Component(gameObject)
	,m_StartingLives(lives)
	, m_CurrentLives(lives)
{
	m_TopMostPos = m_GameObject.lock()->GetComponent<dae::Transform>()->GetPosition();
	for (size_t i = 0; i < size_t(m_StartingLives); ++i)
		SpawnLife();
}

void HealthComponent::Update(float)
{
	if (m_IsDead) 
	{
		m_CurrentLives = m_StartingLives;
		m_IsDead = false;
	};
}

int HealthComponent::GetCurrentLives() const
{
	return m_CurrentLives;
}

void HealthComponent::SpawnLife()
{
	auto newGameObj = std::make_shared<dae::GameObject>();
	auto t = newGameObj->GetComponent<dae::Transform>();
	newGameObj->GetComponent<dae::Transform>()->SetPosition(m_TopMostPos);
	newGameObj->GetComponent<dae::Transform>()->SetSize(m_Size, m_Size, 0.0f);
	auto picture = dae::ResourceManager::GetInstance().LoadTexture("../Data/Sprites/LifeIcon.png");
	auto texture = std::make_shared<dae::TextureComponent>(newGameObj, picture);
	newGameObj->AddComponent(texture);
	m_GameObject.lock()->AddChild(newGameObj);
	m_LivesDisplay.emplace_back(newGameObj);
	m_TopMostPos.y += m_Distance + m_Size;
}

void HealthComponent::RemoveLife()
{
	if (m_CurrentLives > 1)
	{
		--m_CurrentLives;
		m_TopMostPos.y -= m_Distance + m_Size;
		auto children = m_GameObject.lock()->GetChildren();
		m_GameObject.lock()->RemoveChild(children[children.size() - 1]);
		m_LivesDisplay.pop_back();
	}
	else
	{
		m_IsDead = true;
		std::cout << "dead" << std::endl;
	}
}

void HealthComponent::onNotify(const std::string&)
{
	RemoveLife();
}

std::shared_ptr<dae::Component> HealthComponent::Clone(const std::shared_ptr<dae::GameObject>& gameObject)
{
	return std::make_shared<HealthComponent>(gameObject, m_StartingLives);
}

bool HealthComponent::IsDead() const
{
	return m_IsDead;
}
