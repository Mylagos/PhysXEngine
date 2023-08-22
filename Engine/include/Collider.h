#pragma once
#include "Vector2D.h"
#include <vector>
enum CollisionType { NONE, CIRCLE, RECTANGLE };

class Collider
{
protected:
	Vector2D position_;
public:
	CollisionType collisionType_ = NONE;
	auto clone() const { return std::unique_ptr<Collider>(clone_impl()); }
	virtual Collider* clone_impl() const = 0;

	virtual void UpdateRectPoints(Vector2D) = 0;

	virtual std::vector<Vector2D> ReturnPoints() = 0;
	//Poly to poly
	virtual std::pair<Vector2D, Vector2D> ReturnAABBCollider() = 0;
	static bool SAT(Vector2D axis, std::vector<Vector2D> rect1Points, std::vector<Vector2D> rect2Points, float& mtv);
	//Poly to cricle
	static bool SAT(Vector2D axis, std::vector<Vector2D> rectPoints, float radius, Vector2D circlePos, float& mtv);


	static Vector2D ProjectedPointOnAxis(Vector2D point, Vector2D axis);

	static std::vector<Vector2D> SatAxes(Vector2D axis1, Vector2D axis2);
	static std::vector<Vector2D> SatAxesOpti(Vector2D axis1, Vector2D axis2);

	Vector2D getColPos() { return position_; }
	[[nodiscard]] CollisionType getCollisionType() const { return collisionType_; }
};