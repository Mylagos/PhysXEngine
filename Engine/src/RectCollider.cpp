#include "RectCollider.h"

RectCollider::RectCollider(Vector2D widthToHeight, Vector2D position) :
	widthToHeight_(widthToHeight)
{
	position_ = position;
	collisionType_ = RECTANGLE;
	UpdateRectPoints(position_);

}

RectCollider::RectCollider(Vector2D widthToHeight, Vector2D position, float rotation) :
	widthToHeight_(widthToHeight),
	rotationAngle_(-rotation / 360.0f * (2.0f * 3.14f))
{

	collisionType_ = RECTANGLE;
	UpdateRectPoints(position);

}

void RectCollider::UpdateRectPoints(Vector2D pos)
{
	rectPoints_.clear();
	float tempx = widthToHeight_.X() / 2.0f;
	float tempy = widthToHeight_.Y() / 2.0f;
	position_ = pos;
	rectPoints_.emplace_back(Vector2D(-tempx, +tempy));
	rectPoints_.emplace_back(Vector2D(+tempx, +tempy));
	rectPoints_.emplace_back(Vector2D(+tempx, -tempy));
	rectPoints_.emplace_back(Vector2D(-tempx, -tempy));
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
	float radius = sqrt(widthToHeight_.X() / 2 + widthToHeight_.Y() / 2);
	Vector2D minmin(position_.X() - radius, position_.Y() - radius);
	Vector2D maxmax(position_.X() + radius, position_.Y() + radius);
	return { minmin,maxmax };
}
