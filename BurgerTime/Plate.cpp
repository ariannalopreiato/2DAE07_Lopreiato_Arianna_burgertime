#include "Plate.h"

Plate::Plate(const std::shared_ptr<dae::GameObject>& gameObject)
	:Component(gameObject)
{}

void Plate::AddIngredient(const std::shared_ptr<dae::GameObject>& ingredient)
{
	m_IngredientsOnPlate.emplace_back(ingredient);
}

void Plate::Reset()
{
	m_IngredientsOnPlate.clear();
}

bool Plate::IsComplete()
{
	//if (m_IngredientsOnPlate[0].GetIngredientType() == IngredientType::bunBottom
	//	&& m_IngredientsOnPlate[m_IngredientsOnPlate.size() - 1].GetIngredientType() == IngredientType::bunTop)
	//	return true;
	//else
		return false;
}

std::shared_ptr<dae::Component>Plate::Clone(const std::shared_ptr<dae::GameObject>& gameObject)
{
	return std::make_shared<Plate>(gameObject);
}
