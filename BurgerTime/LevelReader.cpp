#include "LevelReader.h"
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <assert.h>

void LevelReader::ReadLevel(const std::string& path)
{
	std::fstream levelFile;
	levelFile.open(path, std::ios::in);
	assert(levelFile.is_open());

	std::vector<std::string> file;

	int maxCols{};
	int maxRows{};
	std::string line{};
	while (std::getline(levelFile, line))
	{
		if (line.size() > maxCols)
			maxCols = int(line.size()); //find the max amount of cols
		++maxRows; //find the max amount of rows
		file.emplace_back(line);
	}

	if (!LevelCreator::IsArrayInitialized())
	{
		LevelCreator::SetArraySize(maxCols, maxRows);
	}

	int currentCol{};
	int currentRow{};
	for (size_t currentLine = 0; currentLine < file.size(); ++currentLine)
	{
		for (size_t currentChar = 0; currentChar < file.at(currentLine).size(); ++currentChar)
		{
			auto current = file.at(currentLine);
			if (current.at(currentChar) == 'x')
			{
				LevelCreator::SpawnStairTop(currentCol, currentRow, m_StairTopSize);
				assert(current.at(currentChar + 1) == 'x' && current.at(currentChar + 2) == 'x');
				currentChar += m_StairTopSize - 1;
				currentCol += m_StairTopSize - 1;
			}
			else if (current.at(currentChar) == 'H')
				LevelCreator::SpawnStair(currentCol, currentRow, true);

			else if (current.at(currentChar) == 'o')
			{
				LevelCreator::SpawnFloor(currentCol, currentRow, m_FloorSize);
				assert(current.at(currentChar + 1) == 'o' && current.at(currentChar + 2) == 'o' && current.at(currentChar + 3) == 'o' && current.at(currentChar + 4) == 'o');
				currentChar += m_FloorSize - 1;
				currentCol += m_FloorSize - 1;
			}
			else if (current.at(currentChar) == '-')
			{
				LevelCreator::SpawnPlate(currentCol, currentRow, m_PlateSize);
				assert(current.at(currentChar + 1) == '-' && current.at(currentChar + 2) == '-' && current.at(currentChar + 3) == '-' && current.at(currentChar + 4) == '-');
				currentChar += m_PlateSize - 1;
				currentCol += m_PlateSize - 1;
			}
			else if (current.at(currentChar) == '-')
			{
				LevelCreator::SpawnPlate(currentCol, currentRow, m_PlateSize);
				assert(current.at(currentChar + 1) == '-' && current.at(currentChar + 2) == '-' && current.at(currentChar + 3) == '-' && current.at(currentChar + 4) == '-');
				currentChar += m_PlateSize - 1;
				currentCol += m_PlateSize - 1;
			}
			else if (current.at(currentChar) == 'b')
			{
				LevelCreator::SpawnFloor(currentCol, currentRow, m_FloorSize);
				LevelCreator::SpawnBunTop(currentCol, currentRow, m_IngredientSize);
				assert(current.at(currentChar + 1) == 'b' && current.at(currentChar + 2) == 'b' && current.at(currentChar + 3) == 'b' && current.at(currentChar + 4) == 'b');
				currentChar += m_IngredientSize - 1;
				currentCol += m_IngredientSize - 1;
			}
			else if (current.at(currentChar) == 'B')
			{
				LevelCreator::SpawnFloor(currentCol, currentRow, m_FloorSize);
				LevelCreator::SpawnBunBottom(currentCol, currentRow, m_IngredientSize);
				assert(current.at(currentChar + 1) == 'B' && current.at(currentChar + 2) == 'B' && current.at(currentChar + 3) == 'B' && current.at(currentChar + 4) == 'B');
				currentChar += m_IngredientSize - 1;
				currentCol += m_IngredientSize - 1;
			}
			else if (current.at(currentChar) == 'c')
			{
				LevelCreator::SpawnFloor(currentCol, currentRow, m_FloorSize);
				LevelCreator::SpawnCheese(currentCol, currentRow, m_IngredientSize);
				assert(current.at(currentChar + 1) == 'c' && current.at(currentChar + 2) == 'c' && current.at(currentChar + 3) == 'c' && current.at(currentChar + 4) == 'c');
				currentChar += m_IngredientSize - 1;
				currentCol += m_IngredientSize - 1;
			}
			else if (current.at(currentChar) == 'p')
			{
				LevelCreator::SpawnFloor(currentCol, currentRow, m_FloorSize);
				LevelCreator::SpawnPatty(currentCol, currentRow, m_IngredientSize);
				assert(current.at(currentChar + 1) == 'p' && current.at(currentChar + 2) == 'p' && current.at(currentChar + 3) == 'p' && current.at(currentChar + 4) == 'p');
				currentChar += m_IngredientSize - 1;
				currentCol += m_IngredientSize - 1;
			}
			else if (current.at(currentChar) == 't')
			{
				LevelCreator::SpawnFloor(currentCol, currentRow, m_FloorSize);
				LevelCreator::SpawnTomato(currentCol, currentRow, m_IngredientSize);
				assert(current.at(currentChar + 1) == 't' && current.at(currentChar + 2) == 't' && current.at(currentChar + 3) == 't' && current.at(currentChar + 4) == 't');
				currentChar += m_IngredientSize - 1;
				currentCol += m_IngredientSize - 1;
			}
			else if (current.at(currentChar) == 'l')
			{
				LevelCreator::SpawnFloor(currentCol, currentRow, m_FloorSize);
				LevelCreator::SpawnLattuce(currentCol, currentRow, m_IngredientSize);
				assert(current.at(currentChar + 1) == 'l' && current.at(currentChar + 2) == 'l' && current.at(currentChar + 3) == 'l' && current.at(currentChar + 4) == 'l');
				currentChar += m_IngredientSize - 1;
				currentCol += m_IngredientSize - 1;
			}
			++currentCol;
		}
		++currentRow;
		currentCol = 0;
	}
}

//void LevelReader::ReadIngredients(const std::string& path)
//{
//	std::fstream ingredientFile;
//	ingredientFile.open(path, std::ios::in);
//	assert(ingredientFile.is_open());
//
//	std::vector<std::string> file;
//
//	std::string ingredient{};
//	while (std::getline(ingredientFile, ingredient))
//	{
//		if (ingredient.find("bunTop") != std::string::npos)
//		{
//			SpawnElementsOfRow("bunTop", ingredient);
//		}
//		else if (ingredient.find("bunBottom") != std::string::npos)
//		{
//			SpawnElementsOfRow("bunBottom", ingredient);
//		}
//		else if (ingredient.find("lattuce") != std::string::npos)
//		{
//			SpawnElementsOfRow("lattuce", ingredient);
//		}
//		else if (ingredient.find("patty") != std::string::npos)
//		{
//			SpawnElementsOfRow("patty", ingredient);
//		}
//		else if (ingredient.find("tomato") != std::string::npos)
//		{
//			SpawnElementsOfRow("tomato", ingredient);
//		}
//		else if (ingredient.find("cheese") != std::string::npos)
//		{
//			SpawnElementsOfRow("cheese", ingredient);
//		}
//	}
//}
//
//void LevelReader::SpawnElementsOfRow(const std::string& start, const std::string& currentLine)
//{
//	std::string lineToRead{ currentLine };
//	size_t posName{ lineToRead.find(start) + start.size() + 2}; //position of where to start reading numbers
//	size_t startPos{ posName };
//	while(lineToRead.size() > 0)
//	{
//		size_t rowNum{ lineToRead.find('}') - 1 }; //position of where the second number is
//		std::string numbers{ lineToRead.substr(startPos, rowNum - startPos + 1) };
//		glm::vec2 position{ GetPosition(numbers) };
//		LevelCreator::SpawnIngredient(start, int(position.x), int(position.y));
//		if (lineToRead.at(rowNum + 2) != '\n')
//		{
//			posName = rowNum + 3;
//			lineToRead = lineToRead.substr(posName + 1, lineToRead.size() - posName);
//			startPos = 0;
//		}
//		else
//			break;
//	}
//}
//
//const glm::vec2 LevelReader::GetPosition(const std::string& string)
//{
//	glm::vec2 point;
//	std::stringstream stream(string);
//	std::string number;
//	std::getline(stream, number, ',');
//	point.x = stof(number);
//	std::getline(stream, number);
//	point.y = stof(number);
//	return point;
//}
