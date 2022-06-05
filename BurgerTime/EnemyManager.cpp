#include "EnemyManager.h"
#include "GameObject.h"
#include "LevelCreator.h"
#include <fstream>
#include <cstdlib>
#include <assert.h>

EnemyManager::EnemyManager()
{
	auto ingredients = LevelCreator::GetIngredients();
	for (size_t i = 0; i < ingredients.size(); ++i)
		m_Ingredients.emplace_back(ingredients[i]->GetGameObject());
}

void EnemyManager::Update(float)
{
	if (m_Ingredients.empty())
	{
		auto ingredients = LevelCreator::GetIngredients();
		for (size_t i = 0; i < ingredients.size(); ++i)
			m_Ingredients.emplace_back(ingredients[i]->GetGameObject());
	}
}

void EnemyManager::SetScoreComponent(const std::shared_ptr<dae::GameObject>& scoreComponent)
{
	m_Score.lock() = scoreComponent;
}

void EnemyManager::SpawnAllLevelEnemies(const std::string& path)
{
	std::fstream ingredientFile;
	ingredientFile.open(path, std::ios::in);
	assert(ingredientFile.is_open());

	std::vector<std::string> file;

	std::string enemy{};
	while (std::getline(ingredientFile, enemy))
	{
		if (enemy.find("MrHotDog") != std::string::npos)
			SpawnElementsOfRow("MrHotDog", enemy);

		else if (enemy.find("MrEgg") != std::string::npos)
			SpawnElementsOfRow("MrEgg", enemy);

		else if (enemy.find("MrPickle") != std::string::npos)
			SpawnElementsOfRow("MrPickle", enemy);
	}
}

void EnemyManager::SpawnElementsOfRow(const std::string& start, const std::string& currentLine)
{
	std::string lineToRead{ currentLine };
	size_t posName{ lineToRead.find(start) + start.size() + 2 }; //position of where to start reading numbers
	size_t startPos{ posName };
	//lineToRead = lineToRead.substr(startPos);
	while (lineToRead.size() > 0)
	{
		size_t rowNum{ lineToRead.find('}') - 1 }; //position of where the second number is
		std::string numbers{ lineToRead.substr(startPos, rowNum - startPos + 1) };
		glm::vec2 position{ GetPosition(numbers) };
		if (start == "MrPickle")
			SpawnMrPickle(position.x, position.y);
		else if (start == "MrHotDog")
			SpawnMrHotDog(position.x, position.y);
		else if (start == "MrEgg")
			SpawnMrEgg(position.x, position.y);

		if (rowNum + 2 < int(lineToRead.size()))
		{
			posName = rowNum + 3;
			lineToRead = lineToRead.substr(posName + 1, lineToRead.size() - posName);
			startPos = 0;
		}
		else
			break;
	}
}

const glm::vec2 EnemyManager::GetPosition(const std::string& string)
{
	glm::vec2 point;
	std::stringstream stream(string);
	std::string number;
	std::getline(stream, number, ',');
	point.x = stof(number);
	std::getline(stream, number);
	point.y = stof(number);
	return point;
}

void EnemyManager::SpawnMrEgg(float posX, float posY)
{
	auto enemy = SpawnEnemy(posX, posY);
	auto egg = std::make_shared<MrEggComponent>(enemy);
	enemy->AddComponent(egg);
	m_Enemies.emplace_back(enemy);
}

void EnemyManager::SpawnMrHotDog(float posX, float posY)
{
	auto enemy = SpawnEnemy(posX, posY);
	auto hotDog = std::make_shared<MrHotDogComponent>(enemy);
	enemy->AddComponent(hotDog);
	m_Enemies.emplace_back(enemy);
}

void EnemyManager::SpawnMrPickle(float posX, float posY)
{
	auto enemy = SpawnEnemy(posX, posY);
	auto pickle = std::make_shared<MrPickleComponent>(enemy);
	enemy->AddComponent(pickle);
	m_Enemies.emplace_back(enemy);
}

std::shared_ptr<dae::GameObject> EnemyManager::SpawnEnemy(float posX, float posY)
{
	auto enemyObj = std::make_shared<dae::GameObject>();
	enemyObj->GetComponent<dae::Transform>()->SetPosition(posX, posY, 0.0f);

	auto collisionComponent = std::make_shared<dae::CollisionComponent>(enemyObj);

	auto behaviourComponent = std::make_shared<CharacterBehaviour>(enemyObj);

	enemyObj->AddComponent(collisionComponent);
	enemyObj->AddComponent(behaviourComponent);
	return enemyObj;
}

const std::vector<std::shared_ptr<dae::GameObject>>& EnemyManager::GetEnemies()
{
	return m_Enemies;
}

void EnemyManager::SetPlayerPos(const SDL_Rect& playerPos)
{
	for (size_t i = 0; i < m_Enemies.size(); ++i)
	{
		auto enemy = m_Enemies.at(i)->GetComponentInheritance<EnemyComponent>();
		if(enemy != nullptr)
			enemy->SetPlayerPos(playerPos);
	}
}

void EnemyManager::CleanEnemies()
{
	m_Enemies.clear();
	m_Ingredients.clear();
}
