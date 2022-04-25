#include "Stairs.h"

Stairs::Stairs(const float& left, const float& bottom, const float& width, const float& height)
	:Stairs(Rectf{left, bottom, width, height})
{}

Stairs::Stairs(const Rectf& shape)
	: m_StairShape(shape)
{}

const Rectf& Stairs::GetStairsShape()
{
	return m_StairShape;
}
