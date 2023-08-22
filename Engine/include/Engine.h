#pragma once
#include "KdTree.h"
#include "RigidBody.h"
#include "SFML/Graphics.hpp"
#include <vector>


class Engine
{
private:
	 static std::vector<RigidBody*> bodyList_;
	 static Vector2D gravity_;
	 std::vector<std::pair<RigidBody*, RigidBody*>> listOfCollisions_;
	 static sf::Clock engineClock_;
	 static sf::Time engineDeltaTime_;
	 inline static KdTree kdTree_{};
public:
	static void firstLoopTest();
	static void secondLoopTest();

	 static void addRigidBody(RigidBody* body);
	 static void CheckCollisions(RigidBody* body, int i);
	 static void update_physics();
	 static void update_physicsOpti();
	 static bool ObjectsCollide(RigidBody* rb, RigidBody* rb2);
	 static void ClearBodyList() { bodyList_.clear(); }

	 static void ElasticCollisions(RigidBody* rb1, RigidBody* rb2);
};