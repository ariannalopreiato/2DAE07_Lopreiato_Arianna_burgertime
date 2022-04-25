#pragma once
#include "structs.h"

class Stairs
{
public:
	Stairs(const float& left, const float& bottom, const float& width, const float& height);
	Stairs(const Rectf& shape);
	const Rectf& GetStairsShape();

private:
	Rectf m_StairShape;

};

