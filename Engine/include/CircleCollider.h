#pragma once
#include "Collider.h"

class CircleCollider : public Collider
{
private:
	float radius_ = 0;
public:
	CircleCollider(float radius, Vector2D position);
	std::vector<Vector2D> ReturnPoints() override
	{
		std::cout << "Error : ReturnPoints on circle shape\n";
		return {  };
	}
	void UpdateRectPoints(Vector2D pos) override
	{
		position_ = pos;
	};
	std::pair<Vector2D, Vector2D> ReturnAABBCollider() override;
	float returnRadius() { return radius_; }
};