#pragma once
#include <vector>
#include "Vector2f.h"

namespace dae
{
	namespace utils
	{
		const float g_Pi{ 3.1415926535f };

#pragma region CollisionFunctionality
		struct HitInfo
		{
			float lambda;
			Point2f intersectPoint;
			Vector2f normal;
		};
		bool IsPointInRect(const Point2f& p, const Rectf& r);
		bool IsPointInCircle(const Point2f& p, const Circlef& c);
		bool IsPointInPolygon(const Point2f& p, const std::vector<Point2f>& vertices);
		bool IsPointInPolygon(const Point2f& p, const Point2f* vertices, size_t nrVertices);

		bool IsOverlapping(const Point2f& a, const Point2f& b, const Circlef& c);
		bool IsOverlapping(const Point2f& a, const Point2f& b, const Rectf& r);

		bool IsOverlapping(const Rectf& r1, const Rectf& r2);
		bool IsOverlapping(const Rectf& r, const Circlef& c);
		bool IsOverlapping(const Circlef& c1, const Circlef& c2);
		bool IsOverlapping(const std::vector<Point2f>& vertices, const Circlef& c);
		bool IsOverlapping(const Point2f* vertices, size_t nrVertices, const Circlef& c);
		bool Raycast(const Point2f* vertices, const size_t nrVertices, const Point2f& rayP1, const Point2f& rayP2, HitInfo& hitInfo);
		bool Raycast(const std::vector<Point2f>& vertices, const Point2f& rayP1, const Point2f& rayP2, HitInfo& hitInfo);

		bool IntersectLineSegments(const Point2f& p1, const Point2f& p2, const Point2f& q1, const Point2f& q2, float& outLambda1, float& outLambda2, float epsilon = 1e-6);
		float DistPointLineSegment(const Point2f& p, const Point2f& a, const Point2f& b);
		bool IsPointOnLineSegment(const Point2f& p, const Point2f& a, const Point2f& b);
		bool IntersectRectLine(const Rectf& r, const Point2f& p1, const Point2f& p2, float& intersectMin, float& intersectMax);

#pragma endregion CollisionFunctionality
	}
}