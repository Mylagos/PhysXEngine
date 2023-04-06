#pragma once

#include <memory>

#include "Vector2D.h"
#include "Collider.h"
#include "RectCollider.h"
#include "CircleCollider.h"
#include <vector>

class RigidBody
{

private:
	Vector2D position_;
	Vector2D velocity_;
	float mass_ = 0;

	bool isColliding_ = false;

	std::unique_ptr<Collider> colliderPtr_;


public:

	RigidBody();
	RigidBody(Vector2D position, float radius, float mass);
	RigidBody(Vector2D position, Vector2D widthToHeight, float mass);
	RigidBody(Vector2D position, Vector2D widthToHeight);
	RigidBody(Vector2D position, Vector2D widthToHeight, float mass, float rotation);


	void update(float deltaTime);

	void ApplyVelocity(float deltaTime);
	void AddVelocity(Vector2D);
	void MaxAccelerate(float);

	bool operator < (const RigidBody& rb) const
	{
		return this->getPosition().X() < rb.getPosition().X();
	}

#pragma region GET/SET
	Vector2D getPosition() const { return position_; }
	void setPosition(Vector2D pos) { this->position_ = pos; }
	void setColliding(bool isColliding) { this->isColliding_ = isColliding; }
	[[nodiscard]] bool getColliding() const { return isColliding_; }

	[[nodiscard]] Collider* getCollider() const { return colliderPtr_.get(); }

	[[nodiscard]] Vector2D getVelocity() const { return  velocity_; }
	void setVelocity(Vector2D velocity) { this->velocity_ = velocity; }
#pragma endregion GET/SET
};