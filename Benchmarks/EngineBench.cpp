#pragma once
#include "benchmark/benchmark.h"
#include "../Engine/include/KdTree.h"
#include "../Engine/include/RectCollider.h"
#include "../Engine/include/CircleCollider.h"
#include "../Engine/include/Engine.h"

struct myBodyList
{
	std::vector<std::unique_ptr<RigidBody>> bodyList;

	myBodyList(int number)
	{
		for (int i = 0; i < number; i++)
		{
			//bodyList.emplace_back(new RigidBody(Vector2D(static_cast<float>(i), static_cast<float>(i)), Vector2D(1.0f, 1.0f)));
			RigidBody* body = new RigidBody(Vector2D(static_cast<float>(i+1), static_cast<float>(i+1)), 50.0f);
			//auto body = new RigidBody(Vector2D(static_cast<float>(i), static_cast<float>(i)), Vector2D(1.0f, 1.0f));
			bodyList.emplace_back(body);
		}
	}
	myBodyList(int number, int number2)
	{
		Engine::ClearBodyList();
		bodyList.clear();
		int a = number2;
		for (int i = 0; i < number; i++)
		{
			//bodyList.emplace_back(new RigidBody(Vector2D(static_cast<float>(i), static_cast<float>(i)), Vector2D(1.0f, 1.0f)));
			//RigidBody* body = new RigidBody(Vector2D(static_cast<float>(i + 1), static_cast<float>(i + 1)), 50.0f);
			auto body = new RigidBody(Vector2D(static_cast<float>(i), static_cast<float>(i)), Vector2D(5.0f, 5.0f), 1.0f, i*3);
			bodyList.emplace_back(body);
		}
	}
};



Engine myEngine;

static void EngineLoop_10Rb(benchmark::State& state)
{
	myBodyList bodyList1(10);

	for (auto _ : state)
	{
		myEngine.update_physics();
	}
	myEngine.ClearBodyList();
}
BENCHMARK(EngineLoop_10Rb);

static void EngineLoop_1500Rb_Opti(benchmark::State& state)
{
	myBodyList bodyList1(1500);
	
	for (auto _ : state)
	{
		myEngine.update_physicsOpti();
	}
	myEngine.ClearBodyList();
}
BENCHMARK(EngineLoop_1500Rb_Opti);

static void EngineLoop_10RbSq(benchmark::State& state)
{
	myBodyList bodyList1(10, 2);

	for (auto _ : state)
	{
		myEngine.update_physics();
	}
	myEngine.ClearBodyList();
}
BENCHMARK(EngineLoop_10RbSq);

static void EngineLoop_50Rb(benchmark::State& state)
{
	myBodyList bodyList2(50);

	for (auto _ : state)
	{
		myEngine.update_physics();
	}
	myEngine.ClearBodyList();
}
BENCHMARK(EngineLoop_50Rb);
static void EngineLoop_50RbSq(benchmark::State& state)
{
	myBodyList bodyList2(50, 2);

	for (auto _ : state)
	{
		myEngine.update_physics();
	}
	myEngine.ClearBodyList();
}
BENCHMARK(EngineLoop_50RbSq);

static void EngineLoop_100Rb(benchmark::State& state)
{
	myBodyList bodyList3(100);

	for (auto _ : state)
	{
		myEngine.update_physics();
	}
	myEngine.ClearBodyList();
}
BENCHMARK(EngineLoop_100Rb);
static void EngineLoop_100RbSq(benchmark::State& state)
{
	myBodyList bodyList3(100, 2);

	for (auto _ : state)
	{
		myEngine.update_physics();

	}
	myEngine.ClearBodyList();
}

BENCHMARK(EngineLoop_100RbSq);
static void EngineLoop_300RbSq(benchmark::State& state)
{
	myBodyList bodyList3(300, 2);

	for (auto _ : state)
	{
		myEngine.update_physics();
	}
	myEngine.ClearBodyList();
}
BENCHMARK(EngineLoop_300RbSq);
BENCHMARK_MAIN();