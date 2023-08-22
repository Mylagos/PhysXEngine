#include "RigidBody.h"
#include "Engine.h"

RigidBody::RigidBody()
{
	Engine::addRigidBody(this);
}

RigidBody::RigidBody(RigidBody& other)
{
	position_ = other.position_;
	velocity_ = other.velocity_;
	mass_ = other.mass_;
	isColliding_ = other.isColliding_;
	colliderPtr_ = other.colliderPtr_->clone();
	IsInNode = other.IsInNode;
	phisicCheckDone = other.phisicCheckDone;
}

RigidBody::RigidBody(const Vector2D position, const float radius, const float mass) :
	position_(position),
	mass_(mass),
	colliderPtr_(std::make_unique<CircleCollider>(CircleCollider(radius, position)))

{
	Engine::addRigidBody(this);
}

RigidBody::RigidBody(const Vector2D position, const float radius) :
	position_(position),
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

RigidBody::RigidBody(Vector2D position, Vector2D widthToHeight) :
	position_(position)
{
	colliderPtr_ = std::make_unique<RectCollider>(RectCollider(widthToHeight, position));
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
	ApplyVelocity(deltaTime);
	if (colliderPtr_->getCollisionType() == CollisionType::RECTANGLE)
		colliderPtr_->UpdateRectPoints(position_);
	if (colliderPtr_->getCollisionType() == CollisionType::CIRCLE)
		colliderPtr_->UpdateRectPoints(position_);
}




void RigidBody::AddVelocity(Vector2D force)
{
	velocity_ += force;
}

void RigidBody::MaxAccelerate(float maxAccelerate)
{
	float thisAccelerate = velocity_.X() + velocity_.Y();
	float surplus = thisAccelerate - maxAccelerate;
	Vector2D newVector = Vector2D(velocity_.X() / thisAccelerate * surplus, velocity_.Y() / thisAccelerate * surplus);
	velocity_ = newVector;

}


void RigidBody::ApplyVelocity(float deltaTime)
{
	position_ += velocity_ * deltaTime;
}

