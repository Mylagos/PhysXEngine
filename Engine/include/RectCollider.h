#pragma once
#include "Collider.h"
#include <vector>

class RectCollider : public Collider
{
private:
	float rotationAngle_ = 0;
	Vector2D widthToHeight_;
	std::vector<Vector2D> rectPoints_;
	float outerRadius_;
	float innerRadius_;
	
public:
	virtual RectCollider* clone_impl() const override { return new RectCollider(*this); };
	std::vector<Vector2D> rectRotatedPoints_;
	RectCollider(Vector2D widthToHeight, Vector2D position);
	RectCollider(Vector2D widthToHeight, Vector2D position, float rotation);

	float getInnerRadius() { return innerRadius_; }
	float getOuterRadius() { return outerRadius_; }
	void UpdateRectPoints(Vector2D pos) override;
	void CalculateRotatedRectPoints();
	std::vector<Vector2D> ReturnPoints() override { return rectRotatedPoints_; }
	const std::vector<Vector2D>& ReturnPointsOpti() const { return rectRotatedPoints_; }
	std::pair<Vector2D,Vector2D> ReturnAABBCollider() override;

};