#include "Engine.h"
#ifdef TRACY_ENABLE
#include <tracy/Tracy.hpp>
#endif
Vector2D Engine::gravity_(0.0f, -0.1f);
std::vector<RigidBody*> Engine::bodyList_;
sf::Clock Engine::engineClock_;
sf::Time Engine::engineDeltaTime_;
KdTree kdTree_{};
int nbOfCollisions_ = 0;
float maxAccelerate = 1000.0f;

void Engine::addRigidBody(RigidBody* body)
{
	bodyList_.push_back(body);
}



void Engine::update_physics()
{
#ifdef TRACY_ENABLE
	ZoneScoped;
#endif
	engineDeltaTime_ = engineClock_.restart();
	nbOfCollisions_ = 0;
	int i = 0;

	for (auto& body : bodyList_)
	{
		body->setColliding(false);

	}


	for (auto& body : bodyList_)
	{

		CheckCollisions(body, i);
		body->update(engineDeltaTime_.asSeconds());

		body->AddVelocity(gravity_ * 100.0f);
		if ((body->getVelocity().X() + body->getVelocity().Y()) > maxAccelerate)
		{
			body->MaxAccelerate(maxAccelerate);
		}

		if (body->getPosition().Y() <= 100.0f)
		{
			body->setVelocity(Vector2D(body->getVelocity().X() * 0.99f, 0.0f));
			if (body->getPosition().Y() <= 95.0f)
			{
				body->setPosition(Vector2D(body->getPosition().X(), 100.0f));
			}
		}
		i++;

	}
	int aaa = nbOfCollisions_;
	int ooo;
}
void Engine::update_physicsOpti()
{
#ifdef TRACY_ENABLE
	ZoneScoped;
#endif
	engineDeltaTime_ = engineClock_.restart();
	nbOfCollisions_ = 0;
	kdTree_.InitOpti(bodyList_);
	for (int ooo = 0; ooo < bodyList_.size(); ooo++)
	{
		kdTree_.InsertRbOpti(*bodyList_.at(ooo), ooo);
	}

	firstLoopTest();
	//////////////////////////////////
	std::vector<std::pair<int, int>> collisions = kdTree_.GetCollisions();
	int pastRb1 = 0;
	bool firstIter = true;
	
	for (auto& [firstId, secondId] : collisions)
	{
		RigidBody*& body1 = bodyList_.at(firstId);
		RigidBody*& body2 = bodyList_.at(secondId);
		nbOfCollisions_++;
		if (ObjectsCollide(body1, body2))
		{
			ElasticCollisions(body1, body2);
			body1->setColliding(true);
			body2->setColliding(true);
		}
	}
	////////////////////////////
	//secondLoopTest();
	//kdTree_.PrintTree();
	kdTree_.ResetTree();

	if(nbOfCollisions_ < 20)
		int bfe = 0;
	if (nbOfCollisions_ > 20)
		int bfe = 0;
	int aaa = nbOfCollisions_;
	//std::cout << nbOfCollisions_ << std::endl;
}

void Engine::firstLoopTest()
{
#ifdef TRACY_ENABLE
	ZoneScoped;
#endif
	for (auto& body : bodyList_)
	{
		body->setColliding(false);

		body->update(engineDeltaTime_.asSeconds());

		body->AddVelocity(gravity_ * 100.0f);
		if ((body->getVelocity().X() + body->getVelocity().Y()) > maxAccelerate)
		{
			body->MaxAccelerate(maxAccelerate);
		}

		if (body->getPosition().Y() <= 100.0f)
		{
			body->setVelocity(Vector2D(body->getVelocity().X() * 0.99f, 0.0f));
			if (body->getPosition().Y() <= 95.0f)
			{
				body->setPosition(Vector2D(body->getPosition().X(), 100.0f));
			}
		}

		/*body->update(engineDeltaTime_.asSeconds());

		body->AddVelocity(gravity_ * 100.0f);
		if ((body->getVelocity().X() + body->getVelocity().Y()) > maxAccelerate)
		{
			body->MaxAccelerate(maxAccelerate);
		}

		if (body->getPosition().Y() <= 100.0f)
		{
			body->setVelocity(Vector2D(body->getVelocity().X() * 0.99f, 0.0f));
			if (body->getPosition().Y() <= 95.0f)
			{
				body->setPosition(Vector2D(body->getPosition().X(), 100.0f));
			}
		}*/
	}
}
void Engine::secondLoopTest()
{
#ifdef TRACY_ENABLE
	ZoneScoped;
#endif
	std::vector<std::pair<int, int>> collisions = kdTree_.GetCollisions();
	int pastRb1 = 0;
	bool firstIter = true;
	RigidBody* body1;
	for (auto& [firstId, secondId] : collisions)
	{
		
			body1 = bodyList_.at(firstId);
		
		RigidBody* body2 = bodyList_.at(secondId);
		nbOfCollisions_++;
		if (ObjectsCollide(body1, body2));
		{
			ElasticCollisions(body1, body2);
			body1->setColliding(true);
			body2->setColliding(true);

		}
		if(!body1->phisicCheckDone)
		{
			body1->phisicCheckDone = true;
			body1->update(engineDeltaTime_.asSeconds());

			body1->AddVelocity(gravity_ * 100.0f);
			if ((body1->getVelocity().X() + body1->getVelocity().Y()) > maxAccelerate)
			{
				body1->MaxAccelerate(maxAccelerate);
			}

			if (body1->getPosition().Y() <= 100.0f)
			{
				body1->setVelocity(Vector2D(body1->getVelocity().X() * 0.99f, 0.0f));
				if (body1->getPosition().Y() <= 95.0f)
				{
					body1->setPosition(Vector2D(body1->getPosition().X(), 100.0f));
				}
			}
		}

	}
}


void Engine::CheckCollisions(RigidBody* body, int i)
{
#ifdef TRACY_ENABLE
	ZoneScoped;
#endif
	for (int j = i + 1; j < bodyList_.size(); j++)
	{
		RigidBody* body2 = bodyList_.at(j);
		nbOfCollisions_++;
		if (Engine::ObjectsCollide(body, body2))
		{
			ElasticCollisions(body, body2);
			body->setColliding(true);
			body2->setColliding(true);
		}
	}
}
bool PolyToPoly(RectCollider*& rb1AsRect, RectCollider*& rb2AsRect, float& MTV)
{
#ifdef TRACY_ENABLE
	ZoneScoped;
#endif

	std::vector<Vector2D> axises;

	RectCollider& thisBody = *rb1AsRect;
	RectCollider& theirBody = *rb2AsRect;

	axises = Collider::SatAxes(
		Vector2D(theirBody.ReturnPoints().at(0) - theirBody.ReturnPoints().at(1)),
		Vector2D(theirBody.ReturnPoints().at(0) - theirBody.ReturnPoints().at(1)));

	for (const auto& axis : axises)
	{
		float tempMTV = 0;
		if (!Collider::SAT(axis, thisBody.ReturnPoints(), theirBody.ReturnPoints(), tempMTV))
			return false;

		if (std::abs(MTV) > std::abs(tempMTV))
		{
			MTV = tempMTV;
		}

	}
	return true;
}
bool PolyToPolyOpti(RectCollider*& rb1AsRect, RectCollider*& rb2AsRect, float& MTV)
{
#ifdef TRACY_ENABLE
	ZoneScoped;
#endif

	std::vector<Vector2D> axises;

	RectCollider& thisBody = *rb1AsRect;
	RectCollider& theirBody = *rb2AsRect;

	axises = Collider::SatAxesOpti(
		Vector2D(theirBody.ReturnPointsOpti().at(0) - theirBody.ReturnPointsOpti().at(1)),
		Vector2D(theirBody.ReturnPointsOpti().at(0) - theirBody.ReturnPointsOpti().at(1)));

	for (const auto& axis : axises)
	{
		float tempMTV = 0;
		if (!Collider::SAT(axis, thisBody.ReturnPointsOpti(), theirBody.ReturnPointsOpti(), tempMTV))
			return false;

		if (std::abs(MTV) > std::abs(tempMTV))
		{
			MTV = tempMTV;
		}

	}
	return true;
}
bool PolyToCircle(RectCollider*& rb1AsRect, CircleCollider*& rb2AsCircle, float& MTV)
{
#ifdef TRACY_ENABLE
	ZoneScoped;
#endif

	std::vector<Vector2D> axises;

	RectCollider& thisBody = *rb1AsRect;
	CircleCollider& theirBody = *rb2AsCircle;

	axises = Collider::SatAxes(
		Vector2D(rb1AsRect->ReturnPoints().at(0) - rb1AsRect->ReturnPoints().at(1)),
		Vector2D(rb2AsCircle->getColPos().ReturnClosestPoint(rb1AsRect->ReturnPoints())));

	for (int i = 0; i < 2; i++)
	{
		float tempMTV = 0;
		if (!Collider::SAT(axises.at(i), rb1AsRect->ReturnPoints(), rb2AsCircle->ReturnRadius(), rb2AsCircle->getColPos(), tempMTV))
			return false;
		if (std::abs(MTV) > std::abs(tempMTV))
		{
			MTV = tempMTV;
		}
	}
	return true;
}
bool Engine::ObjectsCollide(RigidBody* rb, RigidBody* rb2)
{
#ifdef TRACY_ENABLE
	ZoneScoped;
#endif

	std::vector<Vector2D> axises;

	//Error if one of the colliders is type none
	if (rb->getCollider() == nullptr || rb2->getCollider() == nullptr)
	{
		std::cout << "Error: One or more rb colliding have base collider\n";
		return false;
	}

	if (rb->getCollider()->getCollisionType() == CollisionType::NONE || rb2->getCollider()->getCollisionType() == CollisionType::NONE)
		std::cout << "Error: One or more rb colliding have base collider\n";

	auto rb1AsRect = dynamic_cast<RectCollider*>(rb->getCollider());
	auto rb2AsRect = dynamic_cast<RectCollider*>(rb2->getCollider());

	auto rb1AsCircle = dynamic_cast<CircleCollider*>(rb->getCollider());
	auto rb2AsCircle = dynamic_cast<CircleCollider*>(rb2->getCollider());

	float MTV = FLT_MAX;


	//Poly to Poly
	if (rb1AsRect != nullptr && rb2AsRect != nullptr)
	{
		if (rb1AsRect->getOuterRadius() + rb2AsRect->getOuterRadius() < rb->getPosition().Distance(rb2->getPosition()))
		{
			return false;
		}
		if (rb1AsRect->getInnerRadius() + rb2AsRect->getInnerRadius() > rb->getPosition().Distance(rb2->getPosition()))
		{
			MTV = rb1AsRect->getInnerRadius() + rb2AsRect->getInnerRadius() - rb->getPosition().Distance(rb2->getPosition());

		}
		if (!PolyToPolyOpti(rb1AsRect, rb2AsRect, MTV))
		{
			return false;
		}

	}

	//Circle to Circle
	if (rb1AsCircle != nullptr && rb2AsCircle != nullptr)
	{
		if (!(rb1AsCircle->ReturnRadius() + rb2AsCircle->ReturnRadius() > rb->getPosition().Distance(rb2->getPosition())))
			return false;
		MTV = rb1AsCircle->ReturnRadius() + rb2AsCircle->ReturnRadius() - rb->getPosition().Distance(rb2->getPosition());
	}

	//Poly to Circle 
	if (rb1AsRect != nullptr && rb2AsCircle != nullptr)
	{
		if (rb1AsRect->getOuterRadius() + rb2AsCircle->ReturnRadius() < rb->getPosition().Distance(rb2->getPosition()))
		{
			return false;
		}
		else if (rb1AsRect->getInnerRadius() + rb2AsCircle->ReturnRadius() > rb->getPosition().Distance(rb2->getPosition()))
		{
			MTV = rb1AsRect->getInnerRadius() + rb2AsCircle->ReturnRadius() - rb->getPosition().Distance(rb2->getPosition());
		}
		else
		{
			axises = Collider::SatAxes(
				Vector2D(rb1AsRect->ReturnPoints().at(0) - rb1AsRect->ReturnPoints().at(1)),
				Vector2D(rb2AsCircle->getColPos().ReturnClosestPoint(rb1AsRect->ReturnPoints())));

			for (int i = 0; i < 2; i++)
			{
				float tempMTV = 0;
				if (!Collider::SAT(axises.at(i), rb1AsRect->ReturnPoints(), rb2AsCircle->ReturnRadius(), rb2AsCircle->getColPos(), tempMTV))
					return false;
				if (std::abs(MTV) > std::abs(tempMTV))
				{
					MTV = tempMTV;
				}
			}
		}
	}

	//Circle on rect
	if (rb2AsRect != nullptr && rb1AsCircle != nullptr)
	{
		if (rb2AsRect->getOuterRadius() + rb1AsCircle->ReturnRadius() < rb->getPosition().Distance(rb2->getPosition()))
		{
			return false;
		}
		else if (rb2AsRect->getInnerRadius() + rb1AsCircle->ReturnRadius() > rb->getPosition().Distance(rb2->getPosition()))
		{
			MTV = rb2AsRect->getInnerRadius() + rb1AsCircle->ReturnRadius() - rb->getPosition().Distance(rb2->getPosition());
		}
		else
		{
			axises = Collider::SatAxes(
				Vector2D(rb2AsRect->ReturnPoints().at(0) - rb2AsRect->ReturnPoints().at(1)),
				Vector2D(rb1AsCircle->getColPos().ReturnClosestPoint(rb2AsRect->ReturnPoints())));

			for (int i = 0; i < 2; i++)
			{
				float tempMTV = 0;
				if (!Collider::SAT(axises.at(i), rb2AsRect->ReturnPoints(), rb1AsCircle->ReturnRadius(), rb1AsCircle->getColPos(), tempMTV))
					return false;
				if (std::abs(MTV) > std::abs(tempMTV))
				{
					MTV = tempMTV;
				}
			}
		}
	}

	Vector2D vectorMTV = (rb->getPosition() - rb2->getPosition()).Normalized();
	vectorMTV = vectorMTV * MTV;
	rb->setPosition(rb->getPosition() += vectorMTV * 0.5f);
	rb2->setPosition(rb2->getPosition() -= vectorMTV * 0.5f);

	return true;
}

void Engine::ElasticCollisions(RigidBody* rb1, RigidBody* rb2)
{
#ifdef TRACY_ENABLE
	ZoneScoped;
#endif
	Vector2D Vn = (rb1->getPosition() - rb2->getPosition()).Normalized();
	Vector2D Vt = Vn.OrthoRight();

	float V1n = Vn.X() * rb1->getVelocity().X() + Vn.Y() * rb1->getVelocity().Y();
	float V1t = Vt.X() * rb1->getVelocity().X() + Vt.Y() * rb1->getVelocity().Y();

	float V2n = Vn.X() * rb2->getVelocity().X() + Vn.Y() * rb2->getVelocity().Y();
	float V2t = Vt.X() * rb2->getVelocity().X() + Vt.Y() * rb2->getVelocity().Y();

	Vector2D V1p(0, 0);
	Vector2D V2p(0, 0);

	V1p.SetX(Vn.X() * V2n + Vt.X() * V1t);
	V1p.SetY(Vn.Y() * V2n + Vt.Y() * V1t);

	V2p.SetX(Vn.X() * V1n + Vt.X() * V2t);
	V2p.SetY(Vn.Y() * V1n + Vt.Y() * V2t);

	rb1->setVelocity(V1p);
	rb2->setVelocity(V2p);
}
