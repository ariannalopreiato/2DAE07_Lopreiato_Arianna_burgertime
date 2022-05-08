#include "Ingredient.h"
#include "GameObject.h"
#include "CollisionComponent.h"

Ingredient::Ingredient(const std::shared_ptr<dae::GameObject>& gameObject, IngredientType type)
    : Component(gameObject)
    , m_Type(type)
{}

const IngredientType& Ingredient::GetIngredientType() const
{
    return m_Type;
}

bool Ingredient::IsFalling() const
{
    return m_IsFalling;
}

void Ingredient::IngredientFall(float x, float y, const std::vector<Enemy>& enemies)
{
    IngredientFall(Point2f{ x, y }, enemies);
}

void Ingredient::IngredientFall(const Point2f& newPosition, const std::vector<Enemy>& enemies)
{
    m_IsFalling = true;
    int enemyOverlap{ 0 };
    auto collision = m_GameObject.lock()->GetComponent<dae::CollisionComponent>();
    for (size_t i = 0; i < enemies.size(); ++i)
    {
        if (collision->IsOverlapping(Rectf{})) //todo pass enemy
            ++enemyOverlap;
    }

    auto shape = collision->m_Shape;
    while (newPosition.y != shape.bottom)
    {
        --shape.bottom;
        collision->m_Shape = shape;
    }
    m_IsFalling = false;

    AssignPoints(enemyOverlap);
}

void Ingredient::AssignPoints(int)
{

}

std::shared_ptr<dae::Component> Ingredient::Clone(const std::shared_ptr<dae::GameObject>& gameObject)
{
    return std::make_shared<Ingredient>(gameObject, m_Type);
}
