#pragma once
#include "structs.h"
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
		const Rectf& GetSource() const;
		virtual std::shared_ptr<Component> Clone(const std::shared_ptr<dae::GameObject>& gameObject) override;
		void SetNewStartingCol(int startCol);
		void SetNewStartingRow(int startRow);
		bool m_CanAnimate{ true };

	private:
		float m_AnimationTime{ 0 };
		int m_AnimationFrame{ 0 };
		const int m_NrFrames{ 0 };
		const int m_Fps{ 0 };
		int m_NrCol{ 0 };
		int m_NrRow{ 0 };
		Rectf m_Source{};
		float m_ExtraSpaceCol{ 0.0f };
		float m_ExtraSpaceRow{ 0.0f };
		std::weak_ptr<TextureComponent> m_Texture;
	};
}