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
		file.push_back(line);
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
				LevelCreator::SpawnStair(currentCol, currentRow);

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
			++currentCol;
		}
		++currentRow;
		currentCol = 0;
	}
}