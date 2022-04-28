#include "Ingredient.h"

Ingredient::Ingredient(IngredientType type, float x, float y)
    :Ingredient(type, Point2f{x, y})
{}

Ingredient::Ingredient(IngredientType type, Point2f position)
    : m_Type(type)
    , m_Position(position)
{}

const IngredientType& Ingredient::GetIngredientType() const
{
    return m_Type;
}

bool Ingredient::IsFalling() const
{
    return m_IsFalling;
}

void Ingredient::IngredientFall(float x, float y)
{
    IngredientFall(Point2f{ x, y });
}

void Ingredient::IngredientFall(Point2f newPosition)
{
    m_IsFalling = true;
    while (newPosition.y != m_Position.y)
    {
        --m_Position.y;
    }
    m_IsFalling = false;
}

bool Ingredient::IsOverlappedByEnemy(const Enemy&)
{
    //if (/*dae::utils::IsOverlapping()*/false)
    //{
    //    m_OverlappingEnemies.push_back(enemy);
    //    return true;
    //}
    //return false;
    return false;
}