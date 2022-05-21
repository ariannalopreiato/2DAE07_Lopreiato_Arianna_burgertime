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
	m_CellHeight = float(640 / m_MaxRow);
	m_CellWidth = float(630 / m_MaxCol);
}

std::shared_ptr<dae::GameObject> LevelCreator::SpawnStair(int col, int row, int repetition)
{
	auto stair = CreateObject("../Data/Sprites/stairs.png", col, row, repetition);
	auto collision = stair->GetComponent<dae::CollisionComponent>();
	int extraSpace{ 5 };
	collision->SetSize(m_CellWidth / 2, m_CellHeight * 2 + extraSpace);
	collision->SetPosition(col * m_CellWidth + m_CellWidth/4, row * m_CellHeight - m_CellHeight - extraSpace);
	m_Stairs.emplace_back(stair);
	return stair;  
}

std::shared_ptr<dae::GameObject> LevelCreator::SpawnFloor(int col, int row, int repetition)
{
	auto floor = CreateObject("../Data/Sprites/floor.png", col, row, repetition);
	m_Floors.emplace_back(floor);
	return floor;
}

std::shared_ptr<dae::GameObject> LevelCreator::SpawnStairTop(int col, int row, int repetition)
{
	auto stairTop = CreateObject("../Data/Sprites/stairTop.png", col, row, repetition);
	return stairTop;
}

std::shared_ptr<dae::GameObject> LevelCreator::SpawnPlate(int col, int row, int repetition)
{
	auto plate = CreateObject("../Data/Sprites/plate.png", col, row, repetition);
	m_Plates.emplace_back(plate);
	return plate;
}

std::shared_ptr<dae::GameObject> LevelCreator::SpawnBunTop(int col, int row, int repetition)
{
	auto bunTop = CreateIngredient("../Data/Sprites/bunTop.png", col, row, repetition);
	return bunTop;
}

std::shared_ptr<dae::GameObject> LevelCreator::SpawnBunBottom(int col, int row, int repetition)
{
	auto bunBottom = CreateIngredient("../Data/Sprites/bunBottom.png", col, row, repetition);
	return bunBottom;
}

std::shared_ptr<dae::GameObject> LevelCreator::SpawnCheese(int col, int row, int repetition)
{
	auto cheese = CreateIngredient("../Data/Sprites/cheese.png", col, row, repetition);
	return cheese;
}

std::shared_ptr<dae::GameObject> LevelCreator::SpawnLattuce(int col, int row, int repetition)
{
	auto lattuce = CreateIngredient("../Data/Sprites/lattuce.png", col, row, repetition);
	return lattuce;
}

std::shared_ptr<dae::GameObject> LevelCreator::SpawnTomato(int col, int row, int repetition)
{
	auto tomato = CreateIngredient("../Data/Sprites/tomato.png", col, row, repetition);
	return tomato;
}

std::shared_ptr<dae::GameObject> LevelCreator::SpawnPatty(int col, int row, int repetition)
{
	auto patty = CreateIngredient("../Data/Sprites/patty.png", col, row, repetition);
	return patty;
}

//std::shared_ptr<dae::GameObject> LevelCreator::SpawnIngredient(const std::string& name, int col, int row, int repetition)
//{
//	auto ingredient = CreateIngredient("../Data/Sprites/"+name+".png", col, row, repetition);
//	m_Ingredients.emplace_back(ingredient);
//	return ingredient;
//}

std::shared_ptr<dae::GameObject> LevelCreator::CreateObject(const std::string& textureName, int col, int row, int repetition)
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
	m_LevelObjects.emplace_back(object);
	return object;
}

std::shared_ptr<dae::GameObject> LevelCreator::CreateIngredient(const std::string& textureName, int col, int row, int repetition)
{
	auto ingredient = CreateObject(textureName, col, row, repetition);
	
	auto ingredietComponent = std::make_shared<Ingredient>(ingredient);

	ingredient->AddComponent(ingredietComponent);

	m_Ingredients.emplace_back(ingredient);

	return ingredient;
}

std::vector<std::shared_ptr<dae::GameObject>> LevelCreator::GetObjects()
{
	return m_LevelObjects;
}

std::vector<std::shared_ptr<dae::GameObject>> LevelCreator::GetPlates()
{
	return m_Plates;
}

std::vector<std::shared_ptr<dae::GameObject>> LevelCreator::GetStairs()
{
	return m_Stairs;
}

std::vector<std::shared_ptr<dae::GameObject>> LevelCreator::GetIngredients()
{
	return m_Ingredients;
}

std::vector<std::shared_ptr<dae::GameObject>> LevelCreator::GetFloors()
{
	return m_Floors;
}
