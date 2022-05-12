#pragma once
#include "MiniginPCH.h"
#include <vector>
#include <memory>
#include "structs.h"
#include "GameObject.h"
#include "CollisionComponent.h"
#include "TextureComponent.h"
#include "Texture2D.h"

//static -> every instance of this class will have the same values
class LevelCreator
{
public:
	static void SetArraySize(int cols, int rows);
	static std::shared_ptr<dae::GameObject> SpawnStair(int col, int row, int repetition = 1);
	static std::shared_ptr<dae::GameObject> SpawnFloor(int col, int row, int repetition = 1);
	static std::shared_ptr<dae::GameObject> SpawnStairTop(int col, int row, int repetition = 1);
	static std::shared_ptr<dae::GameObject> SpawnPlate(int col, int row, int repetition = 1);
	static bool IsArrayInitialized() { return !m_Grid.empty(); }
	static std::shared_ptr<dae::GameObject> CreateObject(const std::string& textureName, int col, int row, int repetition);
	static std::vector<std::shared_ptr<dae::GameObject>> GetObjects();

private:
	LevelCreator(); //no one can make an instance of it
	static size_t CalculateIndex(const size_t row, const size_t col);
	inline static std::vector<int> m_Grid;
	inline static int m_MaxCol{ 0 };
	inline static int m_MaxRow{ 0 };
	inline static float m_CellWidth{ 0 };
	inline static float m_CellHeight{ 0 };
	inline static std::vector<std::shared_ptr<dae::GameObject>> m_LevelObjects;
};

