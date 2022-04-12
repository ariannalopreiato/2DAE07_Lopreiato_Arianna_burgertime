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

SDL_Texture* dae::Texture2D::GetSDLTexture() const
{
	return m_Texture;
}