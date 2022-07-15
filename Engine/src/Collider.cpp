#include "Collider.h"




bool Collider::SAT(Vector2D axis, std::vector<Vector2D> rect1Points, std::vector<Vector2D> rect2Points, float& mtv)
{
	Vector2D normalizedAxis = axis.Normalized();

	float col1Min = std::numeric_limits<float>::max();
	float col1Max = std::numeric_limits<float>::lowest();

	float col2Min = std::numeric_limits<float>::max();
	float col2Max = std::numeric_limits<float>::lowest();

	float mtvMin = std::numeric_limits<float>::max();

	//Projects points of col1 on axis
	for (int i = 0; i<rect1Points.size(); i++)
	{
		const float dotProduct = normalizedAxis.X() * rect1Points.at(i).X() + normalizedAxis.Y() * rect1Points.at(i).Y();

		if (col1Min > dotProduct)
			col1Min = dotProduct;

		if (col1Max < dotProduct)
			col1Max = dotProduct;
	}

	//Projects points of col2 on axis
	for (int i = 0; i < rect2Points.size(); i++)
	{
		const float dotProduct = normalizedAxis.X() * rect2Points.at(i).X() + normalizedAxis.Y() * rect2Points.at(i).Y();

		if (col2Min > dotProduct)
			col2Min = dotProduct;

		if (col2Max < dotProduct)
			col2Max = dotProduct;
	}

	if (col1Max < col2Min || col2Max < col1Min)
		return false;

	else
	{
		if (mtvMin > std::abs(col2Max - col1Min))
		{
			mtvMin = col2Max - col1Min;
			//std::cout << "case1\n";
		}
		if (mtvMin > std::abs(col1Max - col2Min)) {
			mtvMin = col1Max - col2Min;
			//std::cout << "case2\n";
		}
		mtv = mtvMin;
		return true;
	}
}

bool Collider::SAT(Vector2D axis, std::vector<Vector2D> rectPoints, float radius, Vector2D circlePos, float& mtv)
{
	Vector2D normalizedAxis = axis.Normalized();

	float rectMin = std::numeric_limits<float>::max();
	float rectMax = std::numeric_limits<float>::lowest();
	float circleMin = std::numeric_limits<float>::max();
	float circleMax = std::numeric_limits<float>::lowest();
	float mtvMin = std::numeric_limits<float>::max();

	for (int i = 0; i < rectPoints.size(); i++)
	{
		const float dotProduct = normalizedAxis.X() * rectPoints.at(i).X() + normalizedAxis.Y() * rectPoints.at(i).Y();

		if (rectMin > dotProduct)
			rectMin = dotProduct;

		if (rectMax < dotProduct)
			rectMax = dotProduct;
	}

	const float dotProduct = (normalizedAxis.X() * circlePos.X() + normalizedAxis.Y() * circlePos.Y());

	circleMin = dotProduct - radius;
	circleMax = dotProduct + radius;

	if ((circleMin > rectMax) || 
		(circleMax < rectMin))
		return false;

	else
	{
		if (mtvMin > std::abs(circleMax - rectMin))
		{
			mtvMin = circleMax - rectMin;
			//std::cout << "case1\n";
		}
		if (mtvMin > std::abs(rectMax - circleMin)) {
			mtvMin = rectMax - circleMin;
			//std::cout << "case2\n";
		}
		mtv = mtvMin;
		return true;
	}

}

Vector2D Collider::ProjectedPointOnAxis(Vector2D point, Vector2D axis)
{
	const float d1 = (axis.X() * point.X() + axis.Y() * point.Y());
	const float d2 = (axis.X() * axis.X() + axis.Y() * axis.Y());
	return {axis.X() * (d1 / d2), axis.Y() * (d1 / d2)};
}

std::vector<Vector2D> Collider::SatAxes(Vector2D axis1, Vector2D axis2)
{
	std::vector<Vector2D> returnAxes;

	returnAxes.emplace_back(axis1.OrthoLeft());
	returnAxes.emplace_back(axis1);
	returnAxes.emplace_back(axis1.OrthoRight());
	returnAxes.emplace_back(-axis1);
	returnAxes.emplace_back(axis2.OrthoLeft());
	returnAxes.emplace_back(axis2);
	returnAxes.emplace_back(axis2.OrthoRight());
	returnAxes.emplace_back(-axis2);

	return returnAxes;
}
