#pragma once
#include "MiniginPCH.h"
#include <vector>
#include "Component.h"
#include "EnemyComponent.h"
#include "CollisionComponent.h"
#include "TextureComponent.h"

struct Piece
{
	SDL_Rect shapeSize;
	bool hasWalkedOnIt;
};

class Ingredient : public dae::Component
{
public:
	Ingredient(const std::shared_ptr<dae::GameObject>& gameObject);
	void Initialize();
	void Update(float elapsedSec);
	void AssignPoints(int enemyNr);
	const std::vector<Piece>& GetPieces() const;
	void SetHasWalkedOnPiece(const size_t& index);
	virtual std::shared_ptr<Component> Clone(const std::shared_ptr<dae::GameObject>& gameObject) override;

private:
	void ResetPieces();
	bool CheckHitLevelObject();
	void CheckHitIngredient();
	std::shared_ptr<dae::GameObject> FindNextFloor();
	std::vector<Piece> m_Pieces;
	const size_t m_NumPieces{ 5 };
	bool m_ArePiecesInitialized{ false };
	bool m_IsFalling{ false };
	int m_Speed{ 2 };
	int m_PlateIdx{ 0 };
	bool m_IsFallingOnPlate{ false };

	//Components
	std::weak_ptr<dae::CollisionComponent> m_Collision;
	std::weak_ptr<dae::TextureComponent> m_Texture;
	std::weak_ptr<dae::Transform> m_Transform;

	std::vector<std::shared_ptr<dae::GameObject>> m_Floors;
	std::vector<std::shared_ptr<dae::GameObject>> m_LevelIngredients;
	std::vector<std::shared_ptr<dae::GameObject>> m_Plates;
	std::shared_ptr<dae::GameObject> m_CurrentPlatform;
	std::shared_ptr<dae::GameObject> m_NextPlatform;
};