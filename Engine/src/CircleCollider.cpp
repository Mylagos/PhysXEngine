#include "CircleCollider.h"

CircleCollider::CircleCollider(float radius, Vector2D position) : radius_(radius)
{
	position_ = position;
	collisionType_ = CollisionType::CIRCLE;
}

std::pair<Vector2D, Vector2D> CircleCollider::ReturnAABBCollider()
{
	Vector2D minmin = Vector2D(position_.X() - radius_, position_.Y() - radius_);
	Vector2D maxmax = Vector2D(position_.X() + radius_, position_.Y() + radius_);
	return {minmin, maxmax};
}
