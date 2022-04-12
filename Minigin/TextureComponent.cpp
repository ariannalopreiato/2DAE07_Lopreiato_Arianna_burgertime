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
}

void dae::TextureComponent::Render() const
{
	const auto& pos = m_Transform.lock()->GetPosition();
	dae::Renderer::GetInstance().RenderTexture(*m_Texture, pos.x, pos.y);
}

void dae::TextureComponent::SetPosition(float x, float y)
{
	m_Transform.lock()->SetPosition(x, y, 0);
}

std::shared_ptr<dae::Component> dae::TextureComponent::Clone(const std::shared_ptr<dae::GameObject>& gameObject)
{
	return std::make_shared<TextureComponent>(gameObject, m_Texture);
}

std::shared_ptr<dae::Texture2D> dae::TextureComponent::GetSDLTexture() const
{
	return m_Texture;
}