#pragma once
#include "MiniginPCH.h"
#include "Component.h"
#include "structs.h"
#include "EnemyComponent.h"
#include "CollisionComponent.h"
#include "TextureComponent.h"
#include "Ingredient.h"

class IngredientManager : public dae::Component
{
public:
	IngredientManager(const std::shared_ptr<dae::GameObject>& gameObject);
	std::shared_ptr<dae::GameObject> SpawnIngredientAtPosition(const Point2f& position);
	virtual std::shared_ptr<Component> Clone(const std::shared_ptr<dae::GameObject>& gameObject) override;

private:
};

