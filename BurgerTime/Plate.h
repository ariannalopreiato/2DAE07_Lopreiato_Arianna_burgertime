#pragma once
#include <vector>
#include "Ingredient.h"

class Plate
{
public:
	void AddIngredient(const Ingredient& ingredient);
	void Reset();
	bool IsComplete();


private:
	std::vector<Ingredient> m_IngredientsOnPlate;
	int m_Points{ 100 };
};

