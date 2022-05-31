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
	if (m_IsImageShowing)
	{
		const auto& pos = m_Transform.lock()->GetPosition();
		const auto& size = m_Transform.lock()->GetSize();
		//passes the texture, which part of the sheet to use, where to draw it and how to flip it
		dae::Renderer::GetInstance().RenderTexture(*m_Texture, m_SrcRect, SDL_Rect{ int(pos.x), int(pos.y), int(size.x), int(size.y) }, m_Flip);
	}
}

void dae::TextureComponent::Update(float)
{
	auto texture = GetSDLTexture();

	if (m_SrcRect.w == 0)
		m_SrcRect.w = int(texture->m_Width);

	if(m_SrcRect.h == 0)
		m_SrcRect.h = int(texture->m_Height);
}

void dae::TextureComponent::SetSource(const SDL_Rect& srcRect)
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