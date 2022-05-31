#pragma once
#include "Transform.h"
#include "Component.h"

namespace dae
{
	class Font;
	class Texture2D;
	class GameObject;
	class TextObject final : public Component
	{
	public:
		void Update(float elapsedSec);
		void Render() const;

		void SetText(const std::string& text);
		void SetPosition(float x, float y);
		void SetColor(SDL_Color color);

		TextObject(const std::shared_ptr<GameObject>& gameObject, const std::string& text, const std::shared_ptr<Font>& font);
		virtual std::shared_ptr<Component> Clone(const std::shared_ptr<GameObject>& gameObject) override;

		TextObject(const TextObject& other) = delete;
		TextObject(TextObject&& other) = delete;
		TextObject& operator=(const TextObject& other) = delete;
		TextObject& operator=(TextObject&& other) = delete;

	private:
		bool m_NeedsUpdate{};
		std::string m_Text{};
		std::weak_ptr<Transform> m_Transform{};
		std::shared_ptr<Font> m_Font{};
		std::shared_ptr<Texture2D> m_TextTexture{};
		SDL_Color m_Color{ 255,255,255 };
	};
}
