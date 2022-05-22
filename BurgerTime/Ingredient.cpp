#include "Ingredient.h"
#include "GameObject.h"
#include "CollisionComponent.h"
#include "LevelCreator.h"

Ingredient::Ingredient(const std::shared_ptr<dae::GameObject>& gameObject)
    : Component(gameObject)
{
    m_Transform = m_GameObject.lock()->GetComponent<dae::Transform>();
    auto pos = m_Transform.lock()->GetPosition();
    auto size = m_Transform.lock()->GetSize();
    for (size_t i = 0; i < m_NumPieces; ++i)
    {
        Piece piece{};
        SDL_Rect shape{};
        shape.y = int(pos.y);
        shape.w = int(size.x / m_NumPieces);
        shape.x = int(pos.x + shape.w * i);
        shape.h = int(size.y);

        piece.shapeSize = shape;
        piece.hasWalkedOnIt = false;
        m_Pieces.emplace_back(piece);
    }
}

void Ingredient::Initialize()
{
    m_Collision = m_GameObject.lock()->GetComponent<dae::CollisionComponent>();
    m_Floors = LevelCreator::GetFloors();
    m_LevelIngredients = LevelCreator::GetIngredients();
    m_Plates = LevelCreator::GetPlates();

    for (size_t i = 0; i < m_Floors.size(); ++i)
    {
        auto floorBox = m_Floors.at(i)->GetComponent<dae::CollisionComponent>()->GetCollisionBox();
        auto box = m_Collision.lock()->GetCollisionBox();
        if (floorBox.x == box.x && floorBox.y == box.y)
        {
            m_CurrentPlatform = m_Floors.at(i);
            break;
        }
    }

    //m_NextPlatform = FindNextFloor();
}

void Ingredient::Update(float)
{
    int countTouchedPieces{ 0 };
    for (size_t i = 0; i < m_NumPieces; ++i)
    {
        if (m_Pieces.at(i).hasWalkedOnIt)
            ++countTouchedPieces;
    }
    if (countTouchedPieces == m_NumPieces)
        m_IsFalling = true;

    if (m_IsFalling)
    {
        if (CheckHitLevelObject()) //if it touched the floor under it, it stops falling
            m_IsFalling = false;
        else
        {
            CheckHitIngredient();
            auto currentPos = m_Transform.lock()->GetPosition();
            currentPos.y += m_Speed;
            m_Transform.lock()->SetPosition(currentPos);
        }
    }
}

void Ingredient::AssignPoints(int)
{

}

const std::vector<Piece>& Ingredient::GetPieces() const
{
    return m_Pieces;
}

void Ingredient::ResetPieces()
{
    for (size_t i = 0; i < m_NumPieces; ++i)
    {
        auto pos = m_Transform.lock()->GetPosition();
        m_Pieces.at(i).shapeSize.x = int(pos.x);
        m_Pieces.at(i).shapeSize.y = int(pos.y);
        m_Pieces.at(i).hasWalkedOnIt = false;
    }
}

void Ingredient::SetHasWalkedOnPiece(const size_t& index)
{
    m_Pieces.at(index).hasWalkedOnIt = true;
}

std::shared_ptr<dae::GameObject> Ingredient::FindNextFloor()
{
    auto box = m_Collision.lock()->GetCollisionBox();
    std::shared_ptr<dae::GameObject> nextPlatform{};
    for (size_t i = 0; i < m_Floors.size(); ++i)
    {
        auto floorBox = m_Floors.at(i)->GetComponent<dae::CollisionComponent>()->GetCollisionBox();
        //if the floor is on the same column, is not the current platform and is under the ingredient
        if (floorBox.x == box.x && box.y < floorBox.y && m_Floors.at(i) != m_CurrentPlatform)
        {
            nextPlatform = m_Floors.at(i);
            break;
        }
    }
    if (nextPlatform == nullptr) //if it's not falling on a floor it will fall on a plate
    {
        for (size_t i = 0; i < m_Plates.size(); ++i)
        {
            auto plateBox = m_Plates.at(i)->GetComponent<dae::CollisionComponent>()->GetCollisionBox();
            if (plateBox.x == box.x && box.y < plateBox.y)
            {
                nextPlatform = m_Plates.at(i);
                break;
            }
        }
    }
    return nextPlatform;
}

bool Ingredient::CheckHitLevelObject()
{
    if (m_NextPlatform == nullptr)
        m_NextPlatform = FindNextFloor();

    if (m_NextPlatform != nullptr)
    {
        auto box = m_Collision.lock()->GetCollisionBox();
        auto nextBox = m_NextPlatform->GetComponent<dae::CollisionComponent>()->GetCollisionBox();
        if (box.y >= nextBox.y)
        {
            m_Transform.lock()->SetPosition(float(box.x), float(nextBox.y), 0.0f);
            m_CurrentPlatform = m_NextPlatform;
            m_NextPlatform = FindNextFloor();
            ResetPieces();
            return true;
        }
    }
    else if (m_NextPlatform == nullptr)
        return true;

    return false;    
}

void Ingredient::CheckHitIngredient()
{
    auto box = m_Collision.lock()->GetCollisionBox();
    auto nextBox = m_NextPlatform->GetComponent<dae::CollisionComponent>()->GetCollisionBox();
    for(size_t i = 0; i < m_LevelIngredients.size(); ++i)
    {
        auto ingredientBox = m_LevelIngredients.at(i)->GetComponent<dae::CollisionComponent>()->GetCollisionBox();
        if (nextBox.x == ingredientBox.x && nextBox.y == ingredientBox.y) //if the ingredient is on the next platform
        {
            if (box.x == ingredientBox.x && box.y + box.h >= ingredientBox.y)
                m_LevelIngredients.at(i)->GetComponent<Ingredient>()->m_IsFalling = true;
        }
    }
}

std::shared_ptr<dae::Component> Ingredient::Clone(const std::shared_ptr<dae::GameObject>& gameObject)
{
    return std::make_shared<Ingredient>(gameObject);
}


