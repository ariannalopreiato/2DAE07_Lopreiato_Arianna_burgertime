#include "MiniginPCH.h"
#include "TextureComponent.h"
#include "Renderer.h"
#include "GameObject.h"

dae::TextureComponent::TextureComponent(const std::shared_ptr<GameObject>& gameObject, const std::shared_ptr<Texture2D>& texture)
	:Component(gameObject)
	, m_Texture(texture) 
{
	//gets the transform component from the gameObject so that it can move with it
	m_Transform = gameObject->GetComponent<Transform>();
	m_DstWidth = texture->m_Width;
	m_DstHeight = texture->m_Height;
}

void dae::TextureComponent::Render() const
{
	const auto& pos = m_Transform.lock()->GetPosition();
	//passes the texture, which part of the sheet to use, where to draw it and how to flip it
	dae::Renderer::GetInstance().RenderTexture(*m_Texture, m_SrcRect, Rectf{pos.x, pos.y, m_DstWidth, m_DstHeight }, m_Flip);
}

void dae::TextureComponent::SetPosition(float x, float y)
{
	m_Transform.lock()->SetPosition(x, y, 0);
}

void dae::TextureComponent::SetSource(const Rectf& srcRect)
{
	m_SrcRect = srcRect; //in case the size changes
}

void dae::TextureComponent::SetDestinationSize(float width, float height)
{
	m_DstWidth = width;
	m_DstHeight = height;
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