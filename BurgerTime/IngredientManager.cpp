#include "IngredientManager.h"
#include "GameObject.h"

IngredientManager::IngredientManager(const std::shared_ptr<dae::GameObject>& gameObject)
	:Component(gameObject)
{}

std::shared_ptr<dae::GameObject> IngredientManager::SpawnIngredientAtPosition(const Point2f& position)
{
    auto pIngredient = std::make_shared<dae::GameObject>();
    auto pIngredientComponent = std::make_shared<Ingredient>(pIngredient, IngredientType::cheese);
    auto pCollision = std::make_shared<dae::CollisionComponent>(pIngredient);
    auto pTexture = dae::ResourceManager::GetInstance().LoadTexture("../Data/Sprites/cheese.png");
    auto pTextureComponent = std::make_shared<dae::TextureComponent>(pIngredient, pTexture);
    pIngredient->GetComponent<dae::Transform>()->SetPosition(position.x, position.y, 0.0f);

    pIngredient->AddComponent(pCollision);
    pIngredient->AddComponent(pTextureComponent);
    pIngredient->AddComponent(pIngredientComponent);
	return pIngredient;
}

std::shared_ptr<dae::Component> IngredientManager::Clone(const std::shared_ptr<dae::GameObject>& gameObject)
{
	return std::make_shared<IngredientManager>(gameObject);
}
