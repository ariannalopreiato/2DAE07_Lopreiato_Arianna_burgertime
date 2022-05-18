#include "Ingredient.h"
#include "GameObject.h"
#include "CollisionComponent.h"

Ingredient::Ingredient(const std::shared_ptr<dae::GameObject>& gameObject)
    : Component(gameObject)
{
    m_Transform = m_GameObject.lock()->GetComponent<dae::Transform>();
}

void Ingredient::Update(float)
{

}

bool Ingredient::IsFalling() const
{
    return m_IsFalling;
}

void Ingredient::IngredientFall(const std::vector<EnemyComponent>& enemies)
{
    m_IsFalling = true;
    int enemyOverlap{ 0 };
    auto collision = m_GameObject.lock()->GetComponent<dae::CollisionComponent>();
    for (size_t i = 0; i < enemies.size(); ++i)
    {
        if (collision->IsOverlapping(SDL_Rect{})) //todo pass enemy
            ++enemyOverlap;
    }

    //auto shape = collision->m_Shape;
    //while (newPosition.y != shape.bottom)
    //{
    //    --shape.bottom;
    //    collision->m_Shape = shape;
    //}

    m_IsFalling = false;

    AssignPoints(enemyOverlap);
}

void Ingredient::AssignPoints(int)
{

}

std::shared_ptr<dae::Component> Ingredient::Clone(const std::shared_ptr<dae::GameObject>& gameObject)
{
    return std::make_shared<Ingredient>(gameObject);
}
