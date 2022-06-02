#pragma once
#include "MiniginPCH.h"
#include "GameObject.h"
#include "CollisionComponent.h"
#include "TextureComponent.h"
#include "Texture2D.h"
#include "Ingredient.h"
#include "Plate.h"

//static -> every instance of this class will have the same values
class LevelCreator
{
public:
	static void SetArraySize(int cols, int rows);
	static std::shared_ptr<dae::GameObject> SpawnStair(int col, int row, int repetition = 1);
	static std::shared_ptr<dae::GameObject> SpawnFloor(int col, int row, int repetition = 5);
	static std::shared_ptr<dae::GameObject> SpawnStairTop(int col, int row, int repetition = 3);
	static std::shared_ptr<dae::GameObject> SpawnPlate(int col, int row, int repetition = 5);
	static std::shared_ptr<dae::GameObject> SpawnBunTop(int col, int row, int repetition = 5);
	static std::shared_ptr<dae::GameObject> SpawnBunBottom(int col, int row, int repetition = 5);
	static std::shared_ptr<dae::GameObject> SpawnCheese(int col, int row, int repetition = 5);
	static std::shared_ptr<dae::GameObject> SpawnLattuce(int col, int row, int repetition = 5);
	static std::shared_ptr<dae::GameObject> SpawnTomato(int col, int row, int repetition = 5);
	static std::shared_ptr<dae::GameObject> SpawnPatty(int col, int row, int repetition = 5);
	static bool IsArrayInitialized() { return !m_Grid.empty(); }
	static std::vector<std::shared_ptr<dae::GameObject>> GetObjects();
	static std::vector<std::shared_ptr<dae::CollisionComponent>> GetPlates();
	static std::vector<std::shared_ptr<dae::CollisionComponent>> GetStairs();
	static std::vector<std::shared_ptr<dae::CollisionComponent>> GetIngredients();
	static std::vector<std::shared_ptr<dae::CollisionComponent>> GetPlatforms();

private:
	LevelCreator(); //no one can make an instance of it
	static void SortElements();
	static size_t CalculateIndex(const size_t row, const size_t col);
	static std::shared_ptr<dae::GameObject> CreateObject(const std::string& textureName, int col, int row, int repetition);
	static std::shared_ptr<dae::GameObject> CreateIngredient(const std::string& textureName, int col, int row, int repetition);
	inline static std::vector<int> m_Grid;
	inline static int m_MaxCol{ 0 };
	inline static int m_MaxRow{ 0 };
	inline static float m_CellWidth{ 0 };
	inline static float m_CellHeight{ 0 };
	inline static std::vector<std::shared_ptr<dae::GameObject>> m_LevelObjects;
	inline static std::vector<std::shared_ptr<dae::GameObject>> m_Ingredients;
	inline static std::vector<std::shared_ptr<dae::GameObject>> m_Stairs;
	inline static std::vector<std::shared_ptr<dae::GameObject>> m_Plates;
	inline static std::vector<std::shared_ptr<dae::GameObject>> m_Platforms;
};

