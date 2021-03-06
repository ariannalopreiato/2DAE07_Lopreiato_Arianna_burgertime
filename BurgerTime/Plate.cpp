#include "Plate.h"

Plate::Plate(const std::shared_ptr<dae::GameObject>& gameObject)
	:Component(gameObject)
{}

void Plate::AddIngredient(const std::shared_ptr<dae::GameObject>& ingredient)
{
	m_IngredientsOnPlate.emplace_back(ingredient);
}

int Plate::IngredientsOnPlateAmount() const
{
	return int(m_IngredientsOnPlate.size());
}

std::shared_ptr<dae::GameObject> Plate::GetTopMostIngredient()
{
	if (!m_IngredientsOnPlate.empty())
		return m_IngredientsOnPlate[m_IngredientsOnPlate.size() - 1];
	else
		return 0;
}

std::shared_ptr<dae::Component>Plate::Clone(const std::shared_ptr<dae::GameObject>& gameObject)
{
	return std::make_shared<Plate>(gameObject);
}
