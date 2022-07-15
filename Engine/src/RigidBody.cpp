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

RigidBody::~RigidBody()
{
	
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
	summForce_ = Vector2D(0, 0);
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



/*bool RigidBody::ObjectsCollide(RigidBody* rb, RigidBody* rb2)
{

	std::vector<Vector2D> axises;

	//Error if one of the colliders is type none
	if (rb->getCollider()->getCollisionType() == CollisionType::NONE || rb2->getCollider()->getCollisionType() == CollisionType::NONE)
		std::cout << "Error: One or more rb colliding have base collider\n";

	RectCollider* rb1AsRect = dynamic_cast<RectCollider*>(rb->getCollider());
	RectCollider* rb2AsRect = dynamic_cast<RectCollider*>(rb2->getCollider());

	CircleCollider* rb1AsCircle = dynamic_cast<CircleCollider*>(rb->getCollider());
	CircleCollider* rb2AsCircle = dynamic_cast<CircleCollider*>(rb2->getCollider());


	//Poly to Poly
	if (rb->getCollider()->getCollisionType() == CollisionType::RECTANGLE && rb2->getCollider()->getCollisionType() == CollisionType::RECTANGLE)
	{
		auto Rb1ColPtr = dynamic_cast<RectCollider*>(rb->getCollider());
		auto Rb2ColPtr = dynamic_cast<RectCollider*>(rb2->getCollider());

		//Finds axises of both rectangles
		axises.emplace_back(Vector2D(Rb1ColPtr->ReturnPoints().at(0) - Rb1ColPtr->ReturnPoints().at(1)));
		axises.emplace_back(Vector2D(Rb1ColPtr->ReturnPoints().at(1) - Rb1ColPtr->ReturnPoints().at(2)));

		axises.emplace_back(Vector2D(Rb2ColPtr->ReturnPoints().at(0) - Rb2ColPtr->ReturnPoints().at(1)));
		axises.emplace_back(Vector2D(Rb2ColPtr->ReturnPoints().at(1) - Rb2ColPtr->ReturnPoints().at(2)));

		for (int i = 0; i < axises.size(); i++)
		{
			if (!Collider::SAT(axises.at(i), Rb1ColPtr->ReturnPoints(), Rb2ColPtr->ReturnPoints()))
				return false;
		}
	}

	//Poly to Circle rb2->getCollider()->getCollisionType() == CollisionType::CIRCLE
	if ((rb2->getCollider()->getCollisionType() == CollisionType::CIRCLE || rb->getCollider()->getCollisionType() == CollisionType::CIRCLE)
		&& (rb->getCollider()->getCollisionType() == CollisionType::RECTANGLE || rb2->getCollider()->getCollisionType() == CollisionType::RECTANGLE))
	{
		RectCollider* Rb1ColPtr;
		CircleCollider* Rb2ColPtr;

		if (Rb1ColPtr = dynamic_cast<RectCollider*>(rb->getCollider()));
		else Rb1ColPtr = dynamic_cast<RectCollider*>(rb2->getCollider());

		if (rb2->getCollider()->getCollisionType() == CollisionType::CIRCLE || rb2->getCollider()->getCollisionType() == CollisionType::RECTANGLE)
			Rb2ColPtr = dynamic_cast<CircleCollider*>(rb2->getCollider());
		else Rb2ColPtr = dynamic_cast<CircleCollider*>(rb->getCollider());

		//Finds axises of 1 rectangle
		axises.emplace_back(Vector2D(Rb1ColPtr->ReturnPoints().at(0) - Rb1ColPtr->ReturnPoints().at(1)));
		axises.emplace_back(Vector2D(Rb1ColPtr->ReturnPoints().at(1) - Rb1ColPtr->ReturnPoints().at(2)));
		//Finds axises "opposite?" to first rectangle
		/*axises.emplace_back(Vector2D(axises.at(0) - axises.at(1)));
		axises.emplace_back(Vector2D(-axises.at(0) + axises.at(1)));
for (int i = 0; i < 2; i++)
{
	if (!Collider::SAT(axises.at(i), Rb1ColPtr->ReturnPoints(), Rb2ColPtr->returnRadius(), rb2->getPosition()))
		return false;
}
	}

	//Circle to Circle
	if (rb->getCollider()->getCollisionType() == CollisionType::CIRCLE && rb2->getCollider()->getCollisionType() == CollisionType::CIRCLE)
	{
		auto Rb1ColPtr = dynamic_cast<CircleCollider*>(rb->getCollider());
		auto Rb2ColPtr = dynamic_cast<CircleCollider*>(rb2->getCollider());
		if (!(Rb1ColPtr->returnRadius() + Rb2ColPtr->returnRadius() > rb->getPosition().Distance(rb2->getPosition())))
			return false;
	}

	return true;
}*/