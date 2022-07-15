#pragma once
#include "Collider.h"
#include <vector>

class RectCollider : public Collider
{
private:
	float rotationAngle_ = 0;
	Vector2D widthToHeight_;
	std::vector<Vector2D> rectPoints_;
	std::vector<Vector2D> rectRotatedPoints_;
public:
	RectCollider(Vector2D widthToHeight, Vector2D position);
	RectCollider(Vector2D widthToHeight, Vector2D position, float rotation);

	void UpdateRectPoints(Vector2D pos) override;
	void CalculateRotatedRectPoints();
	std::vector<Vector2D> ReturnPoints() override { return rectRotatedPoints_; }
	std::pair<Vector2D,Vector2D> ReturnAABBCollider() override;

};