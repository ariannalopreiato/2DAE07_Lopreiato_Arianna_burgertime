#include "Ingredient.h"
#include "GameObject.h"
#include "CollisionComponent.h"
#include "LevelCreator.h"
#include "GameManager.h"

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
    m_Floors = LevelCreator::GetPlatforms();
    m_LevelIngredients = LevelCreator::GetIngredients();
    m_Plates = LevelCreator::GetPlates();

    for (size_t i = 0; i < m_Floors.size(); ++i)
    {
        auto floorBox = m_Floors.at(i)->GetCollisionBox();
        auto box = m_Collision.lock()->GetCollisionBox();
        if (floorBox.x == box.x && floorBox.y == box.y)
        {
            m_CurrentPlatform = m_Floors.at(i)->GetGameObject();
            break;
        }
    }
}


void Ingredient::Update(float)
{
    int countTouchedPieces{ 0 };
    for (size_t i = 0; i < m_NumPieces; ++i)
    {
        if (m_Pieces.at(i).hasWalkedOnIt)
            ++countTouchedPieces;
    }
    if (countTouchedPieces == int(m_NumPieces))
        m_IsFalling = true;

    if (m_IsFalling)
    {
        if (CheckHitLevelObject()) //if it touched the floor under it
        {
            if (!m_EnemiesOnIngredient.empty()) //if there are enemies on top of it
            {
                if (m_ContinueFallingCount == int(m_EnemiesOnIngredient.size()) && !m_EnemiesOnIngredient.empty()) //if it fell for the amount of enemies
                {
                    int pointsForEnemies{ 500 };
                    notify(std::to_string(pointsForEnemies * int(m_EnemiesOnIngredient.size())));
                    for (size_t enemies = 0; enemies < m_EnemiesOnIngredient.size(); ++enemies)
                        m_EnemiesOnIngredient[enemies]->GetComponentInheritance<EnemyComponent>()->Die();
                    m_ContinueFallingCount = 0;
                    m_EnemiesOnIngredient.clear();
                    m_IsFalling = false;
                }
                else
                {
                    FindNextFloor();
                    ++m_ContinueFallingCount;
                }
            }
            else
            {
                notify("50");
                m_IsFalling = false; //if there are no enemies on top, it stops
            }
        }

        else
        {              
            CheckHitIngredient(); //if it touches an ingredient it's going to make it fall
            auto currentPos = m_Transform.lock()->GetPosition();
            currentPos.y += m_Speed;
            m_Transform.lock()->SetPosition(currentPos); //position ingredient after fall
        }

        auto currentPos = m_Transform.lock()->GetPosition();
        for (size_t i = 0; i < m_EnemiesOnIngredient.size(); ++i)
        {
            auto enemyPos = m_EnemiesOnIngredient[i]->GetComponent<dae::CollisionComponent>()->GetCollisionBox();
            m_EnemiesOnIngredient[i]->GetComponent<dae::Transform>()->SetPosition(float(enemyPos.x), float(currentPos.y - enemyPos.h), 0.0f);
        }
    }
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

bool Ingredient::IsIngredientFalling()
{
    return m_IsFalling;
}

void Ingredient::AddEnemyOnIngredient(const std::shared_ptr<dae::GameObject>& enemy)
{
    m_EnemiesOnIngredient.emplace_back(enemy);
}

std::shared_ptr<dae::GameObject> Ingredient::FindNextFloor()
{
    auto box = m_Collision.lock()->GetCollisionBox();
    std::shared_ptr<dae::GameObject> nextPlatform{};
    for (size_t i = 0; i < m_Floors.size(); ++i)
    {
        auto floorBox = m_Floors.at(i)->GetCollisionBox();
        //if the floor is on the same column, is not the current platform and is under the ingredient
        if (floorBox.x == box.x && box.y < floorBox.y && m_Floors.at(i)->GetGameObject() != m_CurrentPlatform)
        {
            nextPlatform = m_Floors.at(i)->GetGameObject();
            break;
        }
    }
    if (nextPlatform == nullptr) //if it's not falling on a platform it will fall on a plate
    {
        for (size_t i = 0; i < m_Plates.size(); ++i)
        {
            auto plateBox = m_Plates.at(i)->GetCollisionBox();
            int ingredientAmount = m_Plates[m_PlateIdx]->GetGameObject()->GetComponent<Plate>()->IngredientsOnPlateAmount();
            if (plateBox.x == box.x && box.y < plateBox.y - box.h * ingredientAmount)
            {
                nextPlatform = m_Plates.at(i)->GetGameObject();
                m_IsFallingOnPlate = true;
                m_PlateIdx = int(i);  //save the platforms position
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
        SDL_Rect box = m_Collision.lock()->GetCollisionBox();
        SDL_Rect nextBox = m_NextPlatform->GetComponent<dae::CollisionComponent>()->GetCollisionBox();
        if (m_IsFallingOnPlate)
        {
            int ingredientAmount = m_Plates[m_PlateIdx]->GetGameObject()->GetComponent<Plate>()->IngredientsOnPlateAmount();
            nextBox.y -= box.h * ingredientAmount;
        }
        if (box.y >= nextBox.y)
        {
            m_Transform.lock()->SetPosition(float(box.x), float(nextBox.y), 0.0f);
            m_CurrentPlatform = m_NextPlatform;
            m_NextPlatform = FindNextFloor();
            if (m_NextPlatform == nullptr) //ingredient is on the plate
            {
                m_Plates[m_PlateIdx]->GetGameObject()->GetComponent<Plate>()->AddIngredient(m_GameObject.lock());
                m_IsFallingOnPlate = false;
                m_ContinueFallingCount = int(m_EnemiesOnIngredient.size());
                GameManager::AddIngredient();
            }         
            ResetPieces();
            return true;
        }
    }
    else
    {
        ResetPieces();
        return true;
    }

    return false;    
}

void Ingredient::CheckHitIngredient()
{
    auto box = m_Collision.lock()->GetCollisionBox();
    auto nextBox = m_NextPlatform->GetComponent<dae::CollisionComponent>()->GetCollisionBox();

    for(size_t i = 0; i < m_LevelIngredients.size(); ++i)
    {
        auto ingredientBox = m_LevelIngredients.at(i)->GetCollisionBox();
        if (nextBox.x == ingredientBox.x && nextBox.y == ingredientBox.y) //if the ingredient is on the next platform
        {
            if (box.x == ingredientBox.x && box.y + box.h >= ingredientBox.y) //if the current ingredient touches the next ingredient
                    m_LevelIngredients.at(i)->GetGameObject()->GetComponent<Ingredient>()->m_IsFalling = true;
        }
    }
}

std::shared_ptr<dae::Component> Ingredient::Clone(const std::shared_ptr<dae::GameObject>& gameObject)
{
    return std::make_shared<Ingredient>(gameObject);
}