#pragma once
#include "MiniginPCH.h"
#include "structs.h"
#include "utils.h"
#include <vector>
#include "Enemy.h"
#include "Component.h"

enum class IngredientType 
{
	bunTop, patty, cheese, lattuce, tomato, bunBottom
};

class Ingredient : public dae::Component
{
public:
	Ingredient(const std::shared_ptr<dae::GameObject>& gameObject, IngredientType type);
	const IngredientType& GetIngredientType() const;
	bool IsFalling() const;
	void IngredientFall(float x, float y, const std::vector<Enemy>& enemies);
	void IngredientFall(const Point2f& newPosition, const std::vector<Enemy>& enemies);
	void AssignPoints(int enemyNr);
	virtual std::shared_ptr<Component> Clone(const std::shared_ptr<dae::GameObject>& gameObject) override;
private:
	IngredientType m_Type;
	bool m_IsFalling{ false };
};



