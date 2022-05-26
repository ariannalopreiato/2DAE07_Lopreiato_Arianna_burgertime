#pragma once
#include <vector>
#include "Ingredient.h"
#include "Component.h"
#include "PointComponent.h"

class Plate : public dae::Component
{
public:
	Plate(const std::shared_ptr<dae::GameObject>& gameObject);
	void AddIngredient(const std::shared_ptr<dae::GameObject>& ingredient);
	void Reset();
	bool IsComplete();
	int IngredientsOnPlateAmount() const;
	std::shared_ptr<dae::GameObject> GetTopMostIngredient();
	virtual std::shared_ptr<Component> Clone(const std::shared_ptr<dae::GameObject>& gameObject) override;

private:
	std::vector<std::shared_ptr<dae::GameObject>> m_IngredientsOnPlate;
};

