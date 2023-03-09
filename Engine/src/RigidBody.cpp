#include "RigidBody.h"
#include "Engine.h"

RigidBody::RigidBody()
{
	Engine::addRigidBody(this);
}

RigidBody::RigidBody(const Vector2D position, const float radius, const float mass) :
	position_(position),
	mass_(mass),
	colliderPtr_(std::make_unique<CircleCollider>(CircleCollider(radius, position)))

{
	Engine::addRigidBody(this);
}

RigidBody::RigidBody(const Vector2D position, const Vector2D widthToHeight, const float mass) :
	position_(position),
	mass_(mass),
	colliderPtr_(std::make_unique<RectCollider>(RectCollider(widthToHeight, position)))
{
	Engine::addRigidBody(this);
}

RigidBody::RigidBody(const Vector2D position, const Vector2D widthToHeight, const float mass, float const rotation) :
	position_(position),
	mass_(mass),
	colliderPtr_(std::make_unique<RectCollider>(RectCollider(widthToHeight, position, rotation)))
{
	Engine::addRigidBody(this);
}

void RigidBody::update(float deltaTime)
{
	ResetForce();
	SumForce();
	ApplyForce();
	ApplyVelocity(deltaTime);
	if (colliderPtr_->getCollisionType() == CollisionType::RECTANGLE)
		colliderPtr_->UpdateRectPoints(position_);
	if (colliderPtr_->getCollisionType() == CollisionType::CIRCLE)
		colliderPtr_->UpdateRectPoints(position_);
}


void RigidBody::ResetForce()
{
	forces_.clear();
	summForce_ = Vector2D(0, 0);
}

void RigidBody::AddVelocity(Vector2D force)
{
	velocity_ += force;
}


void RigidBody::SumForce()
{
	for (const auto& f : forces_)
	{
		summForce_ += f;
	}
}

void RigidBody::ApplyForce()
{
	velocity_ += summForce_;
}



void RigidBody::ApplyVelocity(float deltaTime)
{
	position_ += velocity_ * deltaTime;
}

void RigidBody::AddForce(Vector2D newForce)
{
	forces_.emplace_back(newForce);
}

