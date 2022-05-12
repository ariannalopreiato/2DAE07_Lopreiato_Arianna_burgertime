#pragma once
#include <string>
#include "LevelCreator.h"

class LevelReader
{
public:
	LevelReader() {}
	void ReadLevel(const std::string& path);

private:
	static const int m_FloorSize{ 5 };
	static const int m_StairTopSize{ 3 };
	static const int m_PlateSize{ 5 };
};

