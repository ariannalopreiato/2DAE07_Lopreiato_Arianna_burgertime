#include "MiniginPCH.h"
#include "AnimationComponent.h"
#include "GameObject.h"
#include "CollisionComponent.h"
#include "Renderer.h"

dae::AnimationComponent::AnimationComponent(const std::shared_ptr<dae::GameObject>& gameObject, int nrFrames, int fps, int col, int row)
	:Component(gameObject)
	, m_NrFrames(nrFrames)
	, m_Fps(fps)
	, m_NrCol(col)
	, m_NrRow(row)
{}

void dae::AnimationComponent::Update(float elapsedSec)
{
	if (m_CanAnimate)
	{
		m_AnimationTime += elapsedSec * m_Fps;
		m_AnimationFrame = int(m_AnimationTime) % m_Fps;
	}

	if (m_Texture.lock() == nullptr)
		m_Texture = m_GameObject.lock()->GetComponent<dae::TextureComponent>();
	else
	{
		auto spriteSheet = m_Texture.lock()->GetSDLTexture();
		m_Source.w = int(spriteSheet->m_Width / m_NrCol);
		m_Source.h = int(spriteSheet->m_Height / m_NrRow);
		if (m_NrCol > 1)
			m_Source.x = int(float(m_AnimationFrame % m_NrFrames) * m_Source.w + m_ExtraSpaceCol);
		if (m_NrRow > 1)
			m_Source.y = int(float(m_AnimationFrame % m_NrFrames) * m_Source.h + m_ExtraSpaceRow);
	}
}

const SDL_Rect& dae::AnimationComponent::GetSource() const
{
	return m_Source;
}

std::shared_ptr<dae::Component> dae::AnimationComponent::Clone(const std::shared_ptr<dae::GameObject>& gameObject)
{
	return std::make_shared<AnimationComponent>(gameObject, m_NrFrames, m_Fps, m_NrCol, m_NrRow);
}

void dae::AnimationComponent::SetNewStartingCol(int startCol)
{
	m_ExtraSpaceCol = m_Source.w * startCol;
}

void dae::AnimationComponent::SetNewStartingRow(int startRow)
{
	m_ExtraSpaceRow = m_Source.w * startRow;
}
