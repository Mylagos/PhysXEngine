#pragma once
#include "RigidBody.h"
#include "SFML/Graphics.hpp"
#include <vector>

class Engine
{
private:
	 static std::vector<RigidBody*> bodyList_;
	 static Vector2D gravity_;
	 std::vector<std::pair<RigidBody*, RigidBody*>> ooo;
	 static sf::Clock engineClock_;
	 static sf::Time engineDeltaTime_;
public:
	 static void addRigidBody(RigidBody* body);
	 static void CheckCollisions(RigidBody* body, int i);
	 static void update_physics();
	 static bool ObjectsCollide(RigidBody* rb, RigidBody* rb2);

	 static void ElasticCollisions(RigidBody* rb1, RigidBody* rb2);
};