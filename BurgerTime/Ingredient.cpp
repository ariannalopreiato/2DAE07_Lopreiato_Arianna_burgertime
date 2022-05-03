#include "Ingredient.h"

Ingredient::Ingredient(IngredientType type, float x, float y, float width, float height)
    :Ingredient(type, Rectf{x, y, width, height})
{}

Ingredient::Ingredient(IngredientType type, Rectf shape)
    : m_Type(type)
    , m_IngredientShape(shape)
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

    for (int i = 0; i < enemies.size(); ++i)
    {
        if (IsOverlappedByEnemy(enemies[i]))
            ++enemyOverlap;
    }

    AssignPoints(enemyOverlap);

    while (newPosition.y != m_IngredientShape.bottom)
    {
        --m_IngredientShape.bottom;
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

const Point2f Ingredient::GetTopLeftPos()
{
    return Point2f{ m_IngredientShape.left, m_IngredientShape.bottom + m_IngredientShape.height };
}

void Ingredient::AssignPoints(int)
{
}
