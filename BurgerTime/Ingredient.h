#pragma once
#include "structs.h"
#include "utils.h"
#include <vector>
#include "Enemy.h"

enum class IngredientType
{
	bunTop, patty, cheese, lattuce, tomato, bunBottom
};

class Ingredient
{
public:
	Ingredient(IngredientType type, float x, float y, float width, float height);
	Ingredient(IngredientType type, Rectf shape);
	const IngredientType& GetIngredientType() const;
	bool IsFalling() const;
	void IngredientFall(float x, float y, const std::vector<Enemy>& enemies);
	void IngredientFall(const Point2f& newPosition, const std::vector<Enemy>& enemies);
	bool IsOverlappedByEnemy(const Enemy& enemy);
	const Point2f GetTopLeftPos();
	void AssignPoints(int enemyNr);
private:
	IngredientType m_Type;
	Rectf m_IngredientShape;
	int m_Width{ 80 };
	bool m_IsFalling{ false };
};



