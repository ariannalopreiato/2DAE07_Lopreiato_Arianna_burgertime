#include "Ingredient.h"
#include "GameObject.h"
#include "CollisionComponent.h"

Ingredient::Ingredient(const std::shared_ptr<dae::GameObject>& gameObject, IngredientType type)
    : Component(gameObject)
    , m_Type(type)
{
    m_Transform = m_GameObject.lock()->GetComponent<dae::Transform>();
    m_Transform.lock()->SetSize(m_IngredientWidth, m_IngredientHeight, 0.0f);
    m_Transform.lock()->SetPosition(100.0f, 50.0f, 0.0f);
}

void Ingredient::Update(float)
{

}

const IngredientType& Ingredient::GetIngredientType() const
{
    return m_Type;
}

bool Ingredient::IsFalling() const
{
    return m_IsFalling;
}

void Ingredient::IngredientFall(float , float , const std::vector<EnemyComponent>& enemies)
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
    return std::make_shared<Ingredient>(gameObject, m_Type);
}
