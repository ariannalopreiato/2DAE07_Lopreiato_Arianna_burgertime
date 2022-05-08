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
	if (m_Texture.lock() == nullptr)
		m_Texture = m_GameObject.lock()->GetComponent<dae::TextureComponent>();
	if (m_CanAnimate)
	{
		m_AnimationTime += elapsedSec * m_Fps;
		m_AnimationFrame = int(m_AnimationTime) % m_Fps;
	}

	auto spriteSheet = m_Texture.lock()->GetSDLTexture();
	m_Source.width = spriteSheet->m_Width / m_NrCol;
	m_Source.height = spriteSheet->m_Height / m_NrRow;
	if (m_NrCol > 1)
		m_Source.left = float(m_AnimationFrame % m_NrFrames) * m_Source.width + m_ExtraSpaceCol;
	if (m_NrRow > 1)
		m_Source.bottom = float(m_AnimationFrame % m_NrFrames) * m_Source.height + m_ExtraSpaceRow;
}

const Rectf& dae::AnimationComponent::GetSource() const
{
	return m_Source;
}

std::shared_ptr<dae::Component> dae::AnimationComponent::Clone(const std::shared_ptr<dae::GameObject>& gameObject)
{
	return std::make_shared<AnimationComponent>(gameObject, m_NrFrames, m_Fps, m_NrCol, m_NrRow);
}

void dae::AnimationComponent::SetNewStartingCol(int startCol)
{
	m_ExtraSpaceCol = m_Source.width * startCol;
}

void dae::AnimationComponent::SetNewStartingRow(int startRow)
{
	m_ExtraSpaceRow = m_Source.height * startRow;
}
