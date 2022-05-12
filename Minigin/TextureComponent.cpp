#include "MiniginPCH.h"
#include "TextureComponent.h"
#include "Renderer.h"
#include "GameObject.h"

dae::TextureComponent::TextureComponent(const std::shared_ptr<GameObject>& gameObject, const std::shared_ptr<Texture2D>& texture)
	:Component(gameObject)
	, m_Texture(texture) 
{
	m_Transform = m_GameObject.lock()->GetComponent<dae::Transform>();
}

void dae::TextureComponent::Render() const
{
	const auto& pos = m_Transform.lock()->GetPosition();
	const auto& size = m_Transform.lock()->GetSize();
	//passes the texture, which part of the sheet to use, where to draw it and how to flip it
	dae::Renderer::GetInstance().RenderTexture(*m_Texture, m_SrcRect, Rectf{pos.x, pos.y, size.x, size.y }, m_Flip);
}

void dae::TextureComponent::Update(float)
{
	auto texture = GetSDLTexture();

	if (m_SrcRect.width == 0.0f)
		m_SrcRect.width = texture->m_Width;

	if(m_SrcRect.height == 0.0f)
		m_SrcRect.height = texture->m_Height;

	//if (m_DstHeight == 0.0f)
	//{
	//	m_DstHeight = texture->m_Height;
	//	m_Transform.lock()->SetSize(m_DstWidth, m_DstHeight, 0.0f);
	//}

	//if (m_DstWidth == 0.0f)
	//{
	//	m_DstWidth = texture->m_Width;
	//	m_Transform.lock()->SetSize(m_DstWidth, m_DstHeight, 0.0f);
	//}
}

//void dae::TextureComponent::SetPosition(float x, float y)
//{
//	SetPosition(Point2f{ x, y });
//}
//
//void dae::TextureComponent::SetPosition(const Point2f& position)
//{
//	m_Transform.lock()->SetPosition(position.x, position.y, 0);
//}
//
//void dae::TextureComponent::SetSize(float width, float height, float depth)
//{
//	m_Transform.lock()->SetSize(width, height, depth);
//}

void dae::TextureComponent::SetSource(const Rectf& srcRect)
{
	m_SrcRect = srcRect; //in case the size changes
}

void dae::TextureComponent::SetFlip(SDL_RendererFlip flip)
{
	m_Flip = flip; //in case it needs to flip
}

std::shared_ptr<dae::Component> dae::TextureComponent::Clone(const std::shared_ptr<dae::GameObject>& gameObject)
{
	return std::make_shared<TextureComponent>(gameObject, m_Texture);
}

std::shared_ptr<dae::Texture2D> dae::TextureComponent::GetSDLTexture() const
{
	return m_Texture;
}