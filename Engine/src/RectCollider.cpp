#include "RectCollider.h"

RectCollider::RectCollider(Vector2D widthToHeight, Vector2D position) :
widthToHeight_(widthToHeight)
{
	position_ = position;
	collisionType_=CollisionType::RECTANGLE;
	UpdateRectPoints(position_);

}

RectCollider::RectCollider(Vector2D widthToHeight, Vector2D position, float rotation) :
widthToHeight_(widthToHeight),
rotationAngle_(-rotation / 360.0f * (2.0f * 3.14f))
{

	collisionType_ = CollisionType::RECTANGLE;
	UpdateRectPoints(position);

}

void RectCollider::UpdateRectPoints(Vector2D pos)
{
	rectPoints_.clear();
	float tempx = widthToHeight_.X() / 2.0f;
	float tempy = widthToHeight_.Y() / 2.0f;
	position_ = pos;
	rectPoints_.emplace_back(Vector2D(- tempx, + tempy));
	rectPoints_.emplace_back(Vector2D(+ tempx, + tempy));
	rectPoints_.emplace_back(Vector2D(+ tempx, - tempy));
	rectPoints_.emplace_back(Vector2D(- tempx, - tempy));
	CalculateRotatedRectPoints();
}

void RectCollider::CalculateRotatedRectPoints()
{
	rectRotatedPoints_.clear();
		for (auto& rectPoint : rectPoints_)
		{
			rectRotatedPoints_.emplace_back(position_.X() + rectPoint.Rotate(rotationAngle_).X(),
			                                position_.Y() + rectPoint.Rotate(rotationAngle_).Y()
			);
		}
}

std::pair<Vector2D, Vector2D> RectCollider::ReturnAABBCollider()
{
	
	float minX = std::numeric_limits<float>::max();
	float minY = std::numeric_limits<float>::max();
	float maxX = std::numeric_limits<float>::lowest();
	float maxY = std::numeric_limits<float>::lowest();
	for (auto vec : rectRotatedPoints_)
	{
		if (vec.X() > maxX)
			maxX = vec.X();
		if (vec.Y() > maxY)
			maxY = vec.Y();
		if (vec.X() < minX)
			minX = vec.X();
		if (vec.Y() < minY)
			minY = vec.Y();
	}
	Vector2D minmin(minX, minY);
	Vector2D maxmax(maxX,maxY);
	return { minmin,maxmax };
}
