#pragma once
#include "benchmark/benchmark.h"
#include "../Engine/include/KdTree.h"
#include "../Engine/include/RectCollider.h"

struct myBodyList
{
	std::vector<RigidBody*> bodyList;

	myBodyList(int number)
	{
		for (int i = 0; i < number; i++)
		{
			//bodyList.emplace_back(new RigidBody(Vector2D(static_cast<float>(i), static_cast<float>(i)), Vector2D(1.0f, 1.0f)));
			auto body = new RigidBody(Vector2D(static_cast<float>(i), static_cast<float>(i)), Vector2D(1.0f, 1.0f));
			bodyList.emplace_back(body);
		}
	}
};

myBodyList bodyList1(1500);
myBodyList bodyList2(15000);
myBodyList bodyList3(150000);
KdTree kdTree;

static void BM_GeterateSpeedx1500(benchmark::State& state)
{
	for (auto _ : state)
	{
		kdTree.Init(bodyList1.bodyList);
		benchmark::DoNotOptimize(kdTree);
	}

}
BENCHMARK(BM_GeterateSpeedx1500);
static void BM_InsertRBx1500(benchmark::State& state)
{
	for (auto _ : state)
	{
		int i = 0;
		for (auto& body : bodyList1.bodyList)
		{
			kdTree.InsertRb(body, i);
			++i;
		}
		benchmark::DoNotOptimize(kdTree);
	}

}
BENCHMARK(BM_InsertRBx1500);


static void BM_GeterateSpeedx15000(benchmark::State& state)
{
	for (auto _ : state)
	{
		kdTree.Init(bodyList2.bodyList);
		benchmark::DoNotOptimize(kdTree);
	}

}
BENCHMARK(BM_GeterateSpeedx15000);
static void BM_InsertRBx15000(benchmark::State& state)
{
	for (auto _ : state)
	{
		int i = 0;
		for (auto& body : bodyList2.bodyList)
		{
			kdTree.InsertRb(body, i);
			++i;
		}
		benchmark::DoNotOptimize(kdTree);
	}

}
BENCHMARK(BM_InsertRBx15000);


static void BM_GeterateSpeedx150000(benchmark::State& state)
{
	for (auto _ : state)
	{
		kdTree.Init(bodyList3.bodyList);
		benchmark::DoNotOptimize(kdTree);
	}

}
BENCHMARK(BM_GeterateSpeedx150000);
static void BM_InsertRBx150000(benchmark::State& state)
{
	for (auto _ : state)
	{
		int i = 0;
		for (auto& body : bodyList3.bodyList)
		{
			kdTree.InsertRb(body, i);
			++i;
		}
		benchmark::DoNotOptimize(kdTree);
	}

}
BENCHMARK(BM_InsertRBx150000);

BENCHMARK_MAIN();