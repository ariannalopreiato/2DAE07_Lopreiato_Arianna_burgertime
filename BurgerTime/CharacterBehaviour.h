#pragma once
#include "MiniginPCH.h"
#include "Component.h"
#include "Structs.h"
#include "Transform.h"
#include "CollisionComponent.h"

class CharacterBehaviour : public dae::Component
{
public:
	CharacterBehaviour(const std::shared_ptr<dae::GameObject>& gameObject);
	void Update(float elapsedSec);
	bool CanGoLeft();
	bool CanGoRight();
	bool CanGoUp();
	bool CanGoDown();
	void SnapBack();
	void SnapDown();
	const Line& GetLineLeft();
	const Line& GetLineRight();
	virtual std::shared_ptr<Component> Clone(const std::shared_ptr<dae::GameObject>& gameObject) override;

private:
	SDL_Rect m_CollidingPlatform;
	Line m_LineLeft{};
	Line m_LineRight{};
	int m_LineLength{ 3 };
	std::weak_ptr<dae::CollisionComponent> m_Collision;
	std::weak_ptr<dae::Transform> m_Transform;
};

