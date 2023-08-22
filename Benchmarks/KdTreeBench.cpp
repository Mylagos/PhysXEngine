#pragma once
#include "benchmark/benchmark.h"
#include "../Engine/include/KdTree.h"
#include "../Engine/include/RectCollider.h"
#include "../Engine/include/Engine.h"

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


KdTree kdTree;

static void BM_GeterateSpeedx10(benchmark::State& state)
{
	myBodyList bodyList1(10);
	for (auto _ : state)
	{
		kdTree.ResetTree();
		kdTree.InitOpti(bodyList1.bodyList);
		benchmark::DoNotOptimize(kdTree);
	}

}
BENCHMARK(BM_GeterateSpeedx10);
static void BM_InsertRBx10(benchmark::State& state)
{
	myBodyList bodyList1(10);
	kdTree.ResetTree();
	kdTree.InitOpti(bodyList1.bodyList);
	for (auto _ : state)
	{
		int i = 0;
		for (auto& body : bodyList1.bodyList)
		{
			kdTree.InsertRbOpti(*body, i);
			++i;
		}
		benchmark::DoNotOptimize(kdTree);
	}
}
BENCHMARK(BM_InsertRBx10);
static void BM_ReturnCollisionsx10_Opti(benchmark::State& state)
{
	myBodyList bodyList1(10);
	kdTree.ResetTree();
	kdTree.InitOpti(bodyList1.bodyList);
	int i = 0;
	for (auto& body : bodyList1.bodyList)
	{
		kdTree.InsertRbOpti(*body, i);
		i++;
	}
	for (auto _ : state)
	{
		kdTree.GetCollisions();
		benchmark::DoNotOptimize(kdTree);
		kdTree.EmptyCollisions();
	}
}
BENCHMARK(BM_ReturnCollisionsx10_Opti);
static void BM_GeterateSpeedx1500(benchmark::State& state)
{
	myBodyList bodyList1(1500);
	for (auto _ : state)
	{
		kdTree.ResetTree();
		kdTree.Init(bodyList1.bodyList);
		benchmark::DoNotOptimize(kdTree);
	}

}
BENCHMARK(BM_GeterateSpeedx1500);
static void BM_GeterateSpeedx1500_Opti(benchmark::State& state)
{
	myBodyList bodyList1(1500);
	for (auto _ : state)
	{
		kdTree.ResetTree();
		kdTree.InitOpti(bodyList1.bodyList);
		benchmark::DoNotOptimize(kdTree);
	}
}
BENCHMARK(BM_GeterateSpeedx1500_Opti);
static void BM_InsertRBx1500(benchmark::State& state)
{
	myBodyList bodyList1(1500);
	kdTree.ResetTree();
	kdTree.InitOpti(bodyList1.bodyList);
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

static void BM_InsertRBx1500_Opti(benchmark::State& state)
{
	myBodyList bodyList1(1500);
	kdTree.ResetTree();
	kdTree.InitOpti(bodyList1.bodyList);
	int i = 0;
	for (auto _ : state)
	{
		for (auto& body : bodyList1.bodyList)
		{
			kdTree.InsertRbOpti(*body, i);
			++i;
		}
		benchmark::DoNotOptimize(kdTree);
	}
}
BENCHMARK(BM_InsertRBx1500_Opti);

static void BM_ReturnCollisionsx1500_Opti(benchmark::State& state)
{
	myBodyList bodyList1(1500);
	kdTree.ResetTree();
	kdTree.InitOpti(bodyList1.bodyList);
	int i = 0;
	for (auto& body : bodyList1.bodyList)
	{
		kdTree.InsertRbOpti(*body, i);
		i++;
	}
	for (auto _ : state)
	{
		kdTree.GetCollisions();
		benchmark::DoNotOptimize(kdTree);
		kdTree.EmptyCollisions();
	}
}
BENCHMARK(BM_ReturnCollisionsx1500_Opti);

static void BM_KDLoopx1500(benchmark::State& state)
{
	myBodyList bodyList1(1500);
	for (auto _ : state)
	{
		kdTree.EmptyCollisions();
		kdTree.ResetTree();
		kdTree.InitOpti(bodyList1.bodyList);
		int i = 0;
		for (auto& body : bodyList1.bodyList)
		{
			kdTree.InsertRbOpti(*body, i);
			i++;
		}
		kdTree.GetCollisions();
		benchmark::DoNotOptimize(kdTree);
	}
}
BENCHMARK(BM_KDLoopx1500);
static void BM_KDLoopx1500Map(benchmark::State& state)
{
	myBodyList bodyList1(1500);
	for (auto _ : state)
	{
		kdTree.EmptyCollisions();
		kdTree.ResetTree();
		kdTree.InitOpti(bodyList1.bodyList);
		int i = 0;
		for (auto& body : bodyList1.bodyList)
		{
			kdTree.InsertRbOpti(*body, i);
			i++;
		}
		kdTree.GetCollisions();
		benchmark::DoNotOptimize(kdTree);
	}
}
BENCHMARK(BM_KDLoopx1500Map);

static void BM_GeterateSpeedx15000(benchmark::State& state)
{
	myBodyList bodyList2(15000);
	for (auto _ : state)
	{
		kdTree.Init(bodyList2.bodyList);
		benchmark::DoNotOptimize(kdTree);
	}

}
BENCHMARK(BM_GeterateSpeedx15000);
static void BM_GeterateSpeedx15000_Opti(benchmark::State& state)
{
	myBodyList bodyList2(15000);
	for (auto _ : state)
	{
		kdTree.InitOpti(bodyList2.bodyList);
		benchmark::DoNotOptimize(kdTree);
	}

}
BENCHMARK(BM_GeterateSpeedx15000_Opti);
static void BM_InsertRBx15000(benchmark::State& state)
{
	myBodyList bodyList2(15000);
	kdTree.ResetTree();
	kdTree.InitOpti(bodyList2.bodyList);
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
static void BM_InsertRBx15000_Opti(benchmark::State& state)
{
	myBodyList bodyList2(15000);
	kdTree.ResetTree();
	kdTree.InitOpti(bodyList2.bodyList);
	for (auto _ : state)
	{
		int i = 0;
		for (auto& body : bodyList2.bodyList)
		{
			kdTree.InsertRbOpti(*body, i);
			i++;
		}
		benchmark::DoNotOptimize(kdTree);
	}

}
BENCHMARK(BM_InsertRBx15000_Opti);

static void BM_GeterateSpeedx150000(benchmark::State& state)
{
	myBodyList bodyList3(150000);
	for (auto _ : state)
	{
		kdTree.Init(bodyList3.bodyList);
		benchmark::DoNotOptimize(kdTree);
	}

}
BENCHMARK(BM_GeterateSpeedx150000);
static void BM_GeterateSpeedx150000_Opti(benchmark::State& state)
{
	myBodyList bodyList3(150000);
	for (auto _ : state)
	{
		kdTree.InitOpti(bodyList3.bodyList);
		benchmark::DoNotOptimize(kdTree);
	}

}
BENCHMARK(BM_GeterateSpeedx150000_Opti);
static void BM_InsertRBx150000(benchmark::State& state)
{
	myBodyList bodyList3(150000);
	kdTree.ResetTree();
	kdTree.InitOpti(bodyList3.bodyList);
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
static void BM_InsertRBx150000_Opti(benchmark::State& state)
{
	myBodyList bodyList3(150000);
	kdTree.ResetTree();
	kdTree.InitOpti(bodyList3.bodyList);
	for (auto _ : state)
	{
		int i = 0;
		for (auto& body : bodyList3.bodyList)
		{
			kdTree.InsertRbOpti(*body, i);
			i++;
		}
		benchmark::DoNotOptimize(kdTree);
	}

}
BENCHMARK(BM_InsertRBx150000_Opti);

BENCHMARK_MAIN();