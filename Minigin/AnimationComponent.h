#pragma once
#include "Component.h"
#include "TextureComponent.h"
#include "CollisionComponent.h"

namespace dae
{
	class AnimationComponent : public dae::Component
	{
	public:
		AnimationComponent(const std::shared_ptr<dae::GameObject>& gameObject, int nrFrames, int fps, int col, int row);
		void Update(float elapsedSec);
		const SDL_Rect& GetSource() const;
		virtual std::shared_ptr<Component> Clone(const std::shared_ptr<dae::GameObject>& gameObject) override;
		void SetNewStartingCol(int startCol);
		void SetNewStartingRow(int startRow);
		bool m_CanAnimate{ false };

	private:
		float m_AnimationTime{ 0 };
		int m_AnimationFrame{ 0 };
		const int m_NrFrames{ 0 };
		const int m_Fps{ 0 };
		int m_NrCol{ 0 };
		int m_NrRow{ 0 };
		SDL_Rect m_Source{};
		int m_ExtraSpaceCol{ 0 };
		int m_ExtraSpaceRow{ 0 };
		std::weak_ptr<TextureComponent> m_Texture;
	};
}