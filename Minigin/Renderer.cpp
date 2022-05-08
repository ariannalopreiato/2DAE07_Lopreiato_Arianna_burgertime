#include "MiniginPCH.h"
#include "Renderer.h"
#include "SceneManager.h"
#include "Texture2D.h"
#include <chrono>

int GetOpenGLDriverIndex()
{
	auto openglIndex = -1;
	const auto driverCount = SDL_GetNumRenderDrivers();
	for (auto i = 0; i < driverCount; i++)
	{
		SDL_RendererInfo info;
		if (!SDL_GetRenderDriverInfo(i, &info))
			if (!strcmp(info.name, "opengl"))
				openglIndex = i;
	}
	return openglIndex;
}

void dae::Renderer::Init(SDL_Window* window)
{
	m_Window = window;
	m_Renderer = SDL_CreateRenderer(window, GetOpenGLDriverIndex(), SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (m_Renderer == nullptr)
	{
		throw std::runtime_error(std::string("SDL_CreateRenderer Error: ") + SDL_GetError());
	}
}

void dae::Renderer::Render()
{
	const auto& color = GetBackgroundColor();
	SDL_SetRenderDrawColor(m_Renderer, color.r, color.g, color.b, color.a);
	SDL_RenderClear(m_Renderer);

	SceneManager::GetInstance().Render();

	SDL_RenderPresent(m_Renderer);
}

void dae::Renderer::Destroy()
{
	if (m_Renderer != nullptr)
	{
		SDL_DestroyRenderer(m_Renderer);
		m_Renderer = nullptr;
	}
}

void dae::Renderer::RenderTexture(const Texture2D& texture, const float x, const float y) const
{
	SDL_Rect dst{};
	dst.x = static_cast<int>(x);
	dst.y = static_cast<int>(y);
	SDL_QueryTexture(texture.GetSDLTexture(), nullptr, nullptr, &dst.w, &dst.h);
	SDL_RenderCopy(GetSDLRenderer(), texture.GetSDLTexture(), nullptr, &dst);
}

void dae::Renderer::RenderTexture(Texture2D& texture, const Rectf& source, const Rectf& dest, SDL_RendererFlip flip)
{
	SDL_Rect dst{};
	SDL_QueryTexture(texture.GetSDLTexture(), nullptr, nullptr, &dst.w, &dst.h);
	texture.m_Width = float(dst.w);
	texture.m_Height = float(dst.h);
	dst.x = static_cast<int>(dest.left);
	dst.y = static_cast<int>(dest.bottom);
	dst.w = static_cast<int>(dest.width);
	dst.h = static_cast<int>(dest.height);

	SDL_Rect src{};
	src.x = static_cast<int>(source.left);
	src.y = static_cast<int>(source.bottom);
	src.w = static_cast<int>(source.width);
	src.h = static_cast<int>(source.height);




	SDL_RenderCopyEx(GetSDLRenderer(), texture.GetSDLTexture(), &src, &dst, 0, nullptr, flip);
	//SDL_RenderCopy(GetSDLRenderer(), texture.GetSDLTexture(), &src, &dst);
}
//dest -> where
//source -> which part of sprite sheet
//sdl_rendercopyex -> flipping image
//render texture pass the source and dest rect