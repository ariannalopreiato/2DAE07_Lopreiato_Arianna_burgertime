#include "Plate.h"

void Plate::AddIngredient(const Ingredient& ingredient)
{
	m_IngredientsOnPlate.push_back(ingredient);
}

void Plate::Reset()
{
	m_IngredientsOnPlate.clear();
}

bool Plate::IsComplete()
{
	if (m_IngredientsOnPlate[0].GetIngredientType() == IngredientType::bunBottom
		&& m_IngredientsOnPlate[m_IngredientsOnPlate.size() - 1].GetIngredientType() == IngredientType::bunTop)
		return true;
	else
		return false;
}
