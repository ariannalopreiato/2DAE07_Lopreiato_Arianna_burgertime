#pragma once
#include "Component.h"

namespace dae
{
	class FPS final : public Component
	{
	public:
		FPS(const int msPerFrame, const std::shared_ptr<GameObject>& gameObject);
		void Update(float elapsedSec) override;
		int GetFPS() const;
		virtual std::shared_ptr<Component> Clone(const std::shared_ptr<GameObject>& gameObject) override;

	private:
		int m_MsPerFrame;
		int m_Fps{ 0 };
	};
}
