#include "MiniginPCH.h"
#include <SDL_ttf.h>
#include "TextObject.h"
#include "Renderer.h"
#include "Font.h"
#include "Texture2D.h"

dae::TextObject::TextObject(const std::shared_ptr<GameObject>& gameObject, const std::string& text, const std::shared_ptr<Font>& font)
	: Component(gameObject)
	, m_NeedsUpdate(true), m_Text(text), m_Font(font), m_TextTexture(nullptr)
{
	//m_Transform = gameObject->GetComponent<Transform>();
}

void dae::TextObject::Update(float)
{
	if (m_NeedsUpdate)
	{
		const auto surf = TTF_RenderText_Blended(m_Font->GetFont(), m_Text.c_str(), m_Color);
		if (surf == nullptr) 
		{
			throw std::runtime_error(std::string("Render text failed: ") + SDL_GetError());
		}
		auto texture = SDL_CreateTextureFromSurface(Renderer::GetInstance().GetSDLRenderer(), surf);
		if (texture == nullptr) 
		{
			throw std::runtime_error(std::string("Create text texture from surface failed: ") + SDL_GetError());
		}
		SDL_FreeSurface(surf);
		m_TextTexture = std::make_shared<Texture2D>(texture);
		m_NeedsUpdate = false;
	}
}

void dae::TextObject::Render() const
{
	if (m_TextTexture != nullptr)
	{
		const auto& pos = m_Transform.lock()->GetPosition();
		Renderer::GetInstance().RenderTexture(*m_TextTexture, pos.x, pos.y);
	}
}

// This implementation uses the "dirty flag" pattern
void dae::TextObject::SetText(const std::string& text)
{
	m_Text = text;
	m_NeedsUpdate = true;
}

void dae::TextObject::SetPosition(const float x, const float y)
{
	m_Transform.lock()->SetPosition(x, y, 0.0f);
}

void dae::TextObject::SetColor(SDL_Color color)
{
	m_Color = color;
}

dae::Component* dae::TextObject::Clone(const std::shared_ptr<dae::GameObject>& gameObject)
{
	return new TextObject(gameObject, m_Text, m_Font);
}

