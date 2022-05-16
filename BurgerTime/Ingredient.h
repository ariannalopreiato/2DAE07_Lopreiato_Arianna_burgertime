#pragma once
#include "MiniginPCH.h"
#include "structs.h"
#include <vector>
#include "Component.h"
#include "EnemyComponent.h"
#include "CollisionComponent.h"
#include "TextureComponent.h"

enum class IngredientType 
{
	bunTop, patty, cheese, lattuce, tomato, bunBottom
};

class Ingredient : public dae::Component
{
public:
	Ingredient(const std::shared_ptr<dae::GameObject>& gameObject, IngredientType type);
	void Update(float elapsedSec);
	const IngredientType& GetIngredientType() const;
	bool IsFalling() const;
	void IngredientFall(float x, float y, const std::vector<EnemyComponent>& enemies);
	void AssignPoints(int enemyNr);
	virtual std::shared_ptr<Component> Clone(const std::shared_ptr<dae::GameObject>& gameObject) override;
private:
	IngredientType m_Type;
	bool m_IsFalling{ false };
	const float m_IngredientWidth{ 50.f };
	const float m_IngredientHeight{ 10.f };

	//Components
	std::weak_ptr<dae::CollisionComponent> m_Collision;
	std::weak_ptr<dae::TextureComponent> m_Texture;
	std::weak_ptr<dae::Transform> m_Transform;
};