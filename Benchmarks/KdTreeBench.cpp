#include "benchmark/benchmark.h"
#include "../Engine/include/KdTree.h"

struct myBodyList
{
	std::vector<RigidBody*> bodyList;

	myBodyList(int number)
	{
		for (int i = 0; i < number; i++)
		{
			RigidBody body(Vector2D(static_cast<float>(i), static_cast<float>(i)), Vector2D(1.0f,1.0f));
			bodyList.emplace_back(&body);
		}
	}
};

myBodyList bodyList1(15000);
myBodyList bodyList2(200000);
myBodyList bodyList3(300000);

static void BM_GeterateSpeed(benchmark::State& state)
{
	for(auto _ : state)
	{
		KdTree kdTree;
		kdTree.Init(bodyList1.bodyList);
		benchmark::DoNotOptimize(kdTree);
	}

}
BENCHMARK(BM_GeterateSpeed);

BENCHMARK_MAIN();