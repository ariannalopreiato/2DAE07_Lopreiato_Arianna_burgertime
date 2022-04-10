#include "MiniginPCH.h"
#include "Texture2D.h"
#include "Renderer.h"

dae::Texture2D::~Texture2D()
{
	SDL_DestroyTexture(m_Texture);
}

dae::Texture2D::Texture2D(SDL_Texture* texture)
	:m_Texture(texture) 
{}

void dae::Texture2D::SetPosition(const float& x, const float& y)
{
	m_Position.x = x;
	m_Position.y = y;
	m_Position.z = 0;
}

SDL_Texture* dae::Texture2D::GetSDLTexture() const
{
	return m_Texture;
}