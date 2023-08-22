#pragma once
#include "benchmark/benchmark.h"
#include "../Engine/include/KdTree.h"
#include "../Engine/include/RectCollider.h"
#include "../Engine/include/CircleCollider.h"
#include "../Engine/include/Engine.h"

struct myBodyList
{
	std::vector<std::unique_ptr<RigidBody>> bodyList;
	std::vector<RigidBody*> bodyList2;

	myBodyList(int number)
	{
		for (int i = 0; i < number; i++)
		{
			//auto body = new RigidBody(Vector2D(static_cast<float>(i*50), static_cast<float>(i*50)), 50);
			auto body = new RigidBody(Vector2D(static_cast<float>(i), static_cast<float>(i)), Vector2D(0.1f, 0.1f));
			bodyList.emplace_back(body);
		}
	}
	myBodyList(int number, int ooo)
	{
		for (int i = 0; i < number; i++)
		{
			//auto body = new RigidBody(Vector2D(static_cast<float>(i*50), static_cast<float>(i*50)), 50);
			auto body = new RigidBody(Vector2D(static_cast<float>(i), static_cast<float>(i)), Vector2D(1.0f, 1.0f));
			bodyList2.emplace_back(body);
		}
	}
	
};



Engine myEngine;

//static void EngineLoop_1500Rb_Opti(benchmark::State& state)
//{
//	myBodyList bodyList1(10, 2);
//	RigidBody* ooo = new RigidBody(Vector2D(1,1), Vector2D(1.0f, 1.0f));
//	RigidBody* eee = new RigidBody(Vector2D(-1, -1), Vector2D(1.0f, 1.0f));
//	KdTree kdtree;
//	kdtree.InitOpti(bodyList1.bodyList2);
//	for (int i = 0; i < bodyList1.bodyList2.size(); i++)
//	kdtree.InsertRbOpti(bodyList1.bodyList2.at(i), i);
//	kdtree.ReturnCollisions(myEngine.collisions);
//	for (auto _ : state)
//	{
//		Engine::ObjectsCollide(bodyList1.bodyList2.at(kdtree.possibleCollisions_.at(1).first), bodyList1.bodyList2.at(kdtree.possibleCollisions_.at(1).first));
//	}
//	myEngine.ClearBodyList();
//}
//BENCHMARK(EngineLoop_1500Rb_Opti);
//static void EngineLoop_1500Rb_Opti2(benchmark::State& state)
//{
//	myBodyList bodyList1(10);
//	RigidBody* ooo = new RigidBody(Vector2D(1, 1), Vector2D(1.0f, 1.0f));
//	RigidBody* eee = new RigidBody(Vector2D(-1, -1), Vector2D(1.0f, 1.0f));
//	for (auto _ : state)
//	{
//		Engine::ObjectsCollide(ooo, eee);
//	}
//	myEngine.ClearBodyList();
//}
//BENCHMARK(EngineLoop_1500Rb_Opti2);
static void EngineLoop_1500Rb(benchmark::State& state)
{
	myBodyList bodyList1(1500);
	for (auto _ : state)
	{
		myEngine.update_physicsOpti();
		benchmark::DoNotOptimize(myEngine);
	}
	myEngine.ClearBodyList();
}
BENCHMARK(EngineLoop_1500Rb);
static void EngineLoop_1500Rb_(benchmark::State& state)
{
	myBodyList bodyList1(1500);

	for (auto _ : state)
	{
		myEngine.update_physics();
		benchmark::DoNotOptimize(myEngine);
	}
	myEngine.ClearBodyList();
}
BENCHMARK(EngineLoop_1500Rb_);