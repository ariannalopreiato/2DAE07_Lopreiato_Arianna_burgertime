#include "MrEgg.h"
#include "Texture2D.h"

MrEgg::MrEgg(const std::shared_ptr<dae::GameObject>& gameObject)
	:Component(gameObject)
	, Enemy(gameObject)
{
	m_Points = 300;
	m_Texture = dae::ResourceManager::GetInstance().LoadTexture("../Data/Sprites/PeterPepper.png");
}

void MrEgg::Update(float elapsedSec)
{
}

void MrEgg::Render() const
{
}