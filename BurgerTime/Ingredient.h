#pragma once
#include "MiniginPCH.h"
#include "structs.h"
#include <vector>
#include "Component.h"
#include "EnemyComponent.h"
#include "CollisionComponent.h"
#include "TextureComponent.h"

class Ingredient : public dae::Component
{
public:
	Ingredient(const std::shared_ptr<dae::GameObject>& gameObject);
	void Update(float elapsedSec);
	bool IsFalling() const;
	void IngredientFall(const std::vector<EnemyComponent>& enemies);
	void AssignPoints(int enemyNr);
	virtual std::shared_ptr<Component> Clone(const std::shared_ptr<dae::GameObject>& gameObject) override;
private:
	bool m_IsFalling{ false };

	//Components
	std::weak_ptr<dae::CollisionComponent> m_Collision;
	std::weak_ptr<dae::TextureComponent> m_Texture;
	std::weak_ptr<dae::Transform> m_Transform;
};