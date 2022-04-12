#pragma once
#include "Component.h"
#include "ResourceManager.h"

struct SDL_Texture;
namespace dae
{
	/**
	 * Simple RAII wrapper for an SDL_Texture
	 */
	class Texture2D final
	{
	public:
		explicit Texture2D(SDL_Texture* texture);
		~Texture2D();

		SDL_Texture* GetSDLTexture() const;

		Texture2D(const Texture2D&) = delete;
		Texture2D(Texture2D&&) = default;
		Texture2D& operator= (const Texture2D&) = delete;
		Texture2D& operator= (Texture2D&&) = default;

	private:
		SDL_Texture* m_Texture;
	};
}
