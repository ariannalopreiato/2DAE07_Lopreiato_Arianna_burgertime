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
	Ingredient(IngredientType type, float x, float y);
	Ingredient(IngredientType type, Point2f position);
	const IngredientType& GetIngredientType() const;
	bool IsFalling() const;
	void IngredientFall(float x, float y);
	void IngredientFall(Point2f newPosition);
	bool IsOverlappedByEnemy(const Enemy& enemy);

private:
	IngredientType m_Type;
	Point2f m_Position;
	int m_Width{ 80 };
	bool m_IsFalling{ false };
	std::vector<Enemy> m_OverlappingEnemies;
};



