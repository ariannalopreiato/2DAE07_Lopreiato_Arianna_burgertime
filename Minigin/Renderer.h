#pragma once
#include "Singleton.h"
#include "structs.h"

namespace dae
{
	struct CacheTransform
	{
		float matrix[16] = {
			1, 0, 0, 0,
			0, 1, 0, 0,
			0, 0, 1, 0,
			0, 0, 0, 1 };
	};

	class GameObject3D
	{
	public:
		CacheTransform transform;
		int ID;
	};

	class GameObject3DAlt
	{
	public:
		CacheTransform* transform;
		int ID;
	};

	class Texture2D;
	/**
	 * Simple RAII wrapper for the SDL renderer
	 */
	class Renderer final : public Singleton<Renderer>
	{
		SDL_Renderer* m_Renderer{};
		SDL_Window* m_Window{};
		SDL_Color m_clearColor{};
	public:
		void Init(SDL_Window* window);
		void Render();
		void Destroy();

		void RenderTexture(const Texture2D& texture, float x, float y) const;
		void RenderTexture(Texture2D& texture, const Rectf& source, const Rectf& dest, SDL_RendererFlip flip);

		SDL_Renderer* GetSDLRenderer() const { return m_Renderer; }

		const SDL_Color& GetBackgroundColor() const { return m_clearColor; }
		void SetBackgroundColor(const SDL_Color& color) { m_clearColor = color; }
	};
}

