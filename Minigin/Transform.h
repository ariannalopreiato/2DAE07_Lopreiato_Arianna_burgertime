#pragma once
#include "Component.h"
#include "structs.h"
#include <glm/glm.hpp>

namespace dae
{
	class Transform final : public Component
	{
	public:
		Transform(const std::shared_ptr<GameObject>& gameObject);
		const glm::vec3& GetPosition() const { return m_Position; }
		const glm::vec3& GetSize() const { return m_Size; }
		void SetPosition(float x, float y, float z);
		void SetSize(float width, float height, float depth);
		void Scale(float scaleX = 1.0f, float scaleY = 1.0f, float scaleZ = 1.0f);
		virtual std::shared_ptr<Component> Clone(const std::shared_ptr<GameObject>& gameObject) override;

	private:
		glm::vec3 m_Position;
		glm::vec3 m_Size;
	};
}
