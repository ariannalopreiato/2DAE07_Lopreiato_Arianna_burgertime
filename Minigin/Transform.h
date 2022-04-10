#pragma once
#include "Component.h"
#include "GameObject.h"

namespace dae
{
	class Transform final : public Component
	{
	public:
		Transform(const std::shared_ptr<GameObject>& gameObject);
		const glm::vec3& GetPosition() const { return m_Position; }
		void SetPosition(float x, float y, float z);
		virtual Component* Clone(const std::shared_ptr<GameObject>& gameObject) override;

	private:
		glm::vec3 m_Position;
	};
}
