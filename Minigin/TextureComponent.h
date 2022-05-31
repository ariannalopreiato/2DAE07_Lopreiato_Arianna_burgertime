#pragma once
#include "Component.h"
#include "Texture2D.h"
#include "Transform.h"

namespace dae
{
	class GameObject;
	class TextureComponent final : public Component
	{
	public:
		TextureComponent(const std::shared_ptr<GameObject>& gameObject, const std::shared_ptr<Texture2D>& texture);

		void Render() const;
		void Update(float elapsedSec);
		void SetSource(const SDL_Rect& srcRect);
		void SetFlip(SDL_RendererFlip flip);
		std::shared_ptr<Texture2D> GetSDLTexture() const;
		bool m_IsImageFlipped{ false };
		bool m_IsImageShowing{ true };
		virtual std::shared_ptr<Component> Clone(const std::shared_ptr<GameObject>& gameObject) override;

	private:
		std::shared_ptr<Texture2D> m_Texture;
		std::weak_ptr<dae::Transform> m_Transform;
		SDL_Rect m_SrcRect{};
		float m_DstWidth{ 0.0f };
		float m_DstHeight{ 0.0f };
		SDL_RendererFlip m_Flip{ SDL_FLIP_NONE };
	};
}

