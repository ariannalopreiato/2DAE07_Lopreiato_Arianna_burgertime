#pragma once
#include <string>
#include "LevelCreator.h"

class LevelReader
{
public:
	LevelReader() {}
	void ReadLevel(const std::string& path);
	//void ReadIngredients(const std::string& path);
	//void SpawnElementsOfRow(const std::string& start, const std::string& currentLine);
	//const glm::vec2 GetPosition(const std::string& string);

private:
	static const int m_FloorSize{ 5 };
	static const int m_StairTopSize{ 3 };
	static const int m_PlateSize{ 5 };
	static const int m_IngredientSize{ 5 };
};

