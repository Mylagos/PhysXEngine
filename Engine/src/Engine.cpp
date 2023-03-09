#include "Engine.h"

Vector2D Engine::gravity_(0.0f,-0.1f);
std::vector<RigidBody*> Engine::bodyList_;
sf::Clock Engine::engineClock_;
sf::Time Engine::engineDeltaTime_;


void Engine::addRigidBody(RigidBody* body)
{
	bodyList_.emplace_back(body);
}



void Engine::update_physics()
{
	engineDeltaTime_ = engineClock_.restart();

	int i = 0;

	for (auto& body : bodyList_)
		body->setColliding(false);

	for (auto& body : bodyList_)
	{
		
		CheckCollisions(body, i);
		body->update(engineDeltaTime_.asSeconds());

		if(body->getPosition().Y() <= 100.0f)
		{

			Vector2D myVec = Vector2D(0.0f, 0.0f);
			body->setVelocity(myVec);

		}
		else
		{
			
			body->AddVelocity(gravity_*5.0f);
		}
		std::cout << body->getPosition().Y() << std::endl;
		
		i++;
	}
}

 void Engine::CheckCollisions(RigidBody* body, int i)
 {
	 
	 for (int j = i+1; j < bodyList_.size(); j++)
	 {
		 RigidBody* body2 = bodyList_.at(j);
		 if (Engine::ObjectsCollide(body, body2))
		 {
			 ElasticCollisions(body, body2);
			 body->setColliding(true);
			 body2->setColliding(true);
		 }
	 }
 }

 bool Engine::ObjectsCollide(RigidBody* rb, RigidBody* rb2)
 {

	 std::vector<Vector2D> axises;

	 //Error if one of the colliders is type none
	 if (rb->getCollider()->getCollisionType() == CollisionType::NONE || rb2->getCollider()->getCollisionType() == CollisionType::NONE)
		 std::cout << "Error: One or more rb colliding have base collider\n";

	 auto* rb1AsRect = dynamic_cast<RectCollider*>(rb->getCollider());
	 auto* rb2AsRect = dynamic_cast<RectCollider*>(rb2->getCollider());

	 auto* rb1AsCircle = dynamic_cast<CircleCollider*>(rb->getCollider());
	 auto* rb2AsCircle = dynamic_cast<CircleCollider*>(rb2->getCollider());

	 float MTV = FLT_MAX;


	 //Poly to Poly
	 if (rb1AsRect != nullptr && rb2AsRect != nullptr)
	 {

		 axises = Collider::SatAxes(
			 Vector2D(rb2AsRect->ReturnPoints().at(0) - rb2AsRect->ReturnPoints().at(1)),
			 Vector2D(rb2AsRect->ReturnPoints().at(0) - rb2AsRect->ReturnPoints().at(1)));

		 for (const auto& axis : axises)
		 {
			 float tempMTV = 0;
			 if (!Collider::SAT(axis, rb1AsRect->ReturnPoints(), rb2AsRect->ReturnPoints(), tempMTV))
			 	return false;
			
			if(std::abs(MTV) > std::abs(tempMTV))
			{
				MTV = tempMTV;
			}
			
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

	//Circle on rect
	 if (rb2AsRect != nullptr && rb1AsCircle != nullptr)
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

	 Vector2D vectorMTV = (rb->getPosition() - rb2->getPosition()).Normalized();
	 vectorMTV = vectorMTV * MTV;
	 rb->setPosition(rb->getPosition() += vectorMTV * 0.5f);
	 rb2->setPosition(rb2->getPosition() -= vectorMTV * 0.5f);

	 return true;
 }

void Engine::ElasticCollisions(RigidBody* rb1, RigidBody* rb2)
{
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
