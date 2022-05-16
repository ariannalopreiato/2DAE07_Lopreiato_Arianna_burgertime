#include "LevelCreator.h"
#include "GameObject.h"
#include "Renderer.h"

LevelCreator::LevelCreator()
{}

size_t LevelCreator::CalculateIndex(const size_t row, const size_t col)
{
	 return m_MaxCol * row + col;
}

void LevelCreator::SetArraySize(int cols, int rows)
{
	m_Grid.resize(cols * rows);
	m_MaxCol = cols;
	m_MaxRow = rows;
	m_CellHeight = float(480 / m_MaxRow);
	m_CellWidth = float(640 / m_MaxCol);
}

std::shared_ptr<dae::GameObject> LevelCreator::SpawnStair(int col, int row, int repetition)
{
	return CreateObject("../Data/Sprites/stairs.png", col, row, LevelObjectType::stair, repetition);
}

std::shared_ptr<dae::GameObject> LevelCreator::SpawnFloor(int col, int row, int repetition)
{
	return CreateObject("../Data/Sprites/floor.png", col, row, LevelObjectType::floor, repetition);
}

std::shared_ptr<dae::GameObject> LevelCreator::SpawnStairTop(int col, int row, int repetition)
{
	return CreateObject("../Data/Sprites/stairTop.png", col, row, LevelObjectType::stairTop, repetition);
}

std::shared_ptr<dae::GameObject> LevelCreator::SpawnPlate(int col, int row, int repetition)
{
	return CreateObject("../Data/Sprites/plate.png", col, row, LevelObjectType::plate, repetition);
}

std::shared_ptr<dae::GameObject> LevelCreator::CreateObject(const std::string& textureName, int col, int row, LevelObjectType type, int repetition)
{
	auto object = std::make_shared<dae::GameObject>();

	auto transform = object->GetComponent<dae::Transform>();

	float width = m_CellWidth * repetition;
	float startPosX = col * m_CellWidth;
	float startPosY = row * m_CellHeight;

	transform->SetSize(width, m_CellHeight, 0.0f);
	transform->SetPosition(startPosX, startPosY, 0.0f);

	auto picture = dae::ResourceManager::GetInstance().LoadTexture(textureName);
	auto texture = std::make_shared<dae::TextureComponent>(object, picture);

	auto collision = std::make_shared<dae::CollisionComponent>(object);
	collision->m_IsBoxVisible = true;
	object->AddComponent(texture);
	object->AddComponent(collision);
	m_LevelObjects.push_back(object);
	m_ObjectTypes.push_back(type);
	return object;
}

std::vector<std::shared_ptr<dae::GameObject>> LevelCreator::GetObjects()
{
	return m_LevelObjects;
}

std::vector<LevelObjectType> LevelCreator::GetTypes()
{
	return m_ObjectTypes;
}
