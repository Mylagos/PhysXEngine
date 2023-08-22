#pragma once
#include "benchmark/benchmark.h"
#include "../Engine/include/Engine.h"


RigidBody circleBody1 = RigidBody(Vector2D(1.0f, 1.0f), 25.0f, 0.0f);
RigidBody circleBody2 = RigidBody(Vector2D(1.1f, 1.1f), 25.0f, 0.0f);
RigidBody SquareBody1 = RigidBody(Vector2D(1.1f, 1.1f), Vector2D(25.0f, 25.0f), 0.0f, 0.0f);
RigidBody SquareBody2 = RigidBody(Vector2D(1.0f, 1.0f), Vector2D(25.0f, 25.0f), 0.0f, 25.0f);

Engine myEngine;



static void BM_CircleToCircleCollision(benchmark::State& state)
{
	for (auto _ : state)
	{
		myEngine.ObjectsCollide(&circleBody1, &circleBody2);
		benchmark::DoNotOptimize(myEngine);
	}

}
BENCHMARK(BM_CircleToCircleCollision);

static void BM_SquareToSquareCollision(benchmark::State& state)
{
	for (auto _ : state)
	{
		myEngine.ObjectsCollide(&SquareBody1, &SquareBody2);
		benchmark::DoNotOptimize(myEngine);
	}

}
BENCHMARK(BM_SquareToSquareCollision);

static void BM_SquareToCircleCollision(benchmark::State& state)
{
	for (auto _ : state)
	{
		myEngine.ObjectsCollide(&circleBody1, &SquareBody2);
		benchmark::DoNotOptimize(myEngine);
	}

}
BENCHMARK(BM_SquareToCircleCollision);

static void BM_OptimizedSAT_OutsideOfOuterCircle(benchmark::State& state)
{
	for (auto _ : state)
	{
		myEngine.ObjectsCollide(&circleBody1, &circleBody2);
	}
}
BENCHMARK(BM_OptimizedSAT_OutsideOfOuterCircle);

static void BM_OptimizedSAT_InsideOfInnerCircle(benchmark::State& state)
{
	for (auto _ : state)
	{
		myEngine.ObjectsCollide(&circleBody1, &circleBody2);
		myEngine.ObjectsCollide(&circleBody1, &circleBody2);
	}
}
BENCHMARK(BM_OptimizedSAT_InsideOfInnerCircle);

static void BM_OptimizedSAT_RequiredToSAT_SqToSq(benchmark::State& state)
{
	for (auto _ : state)
	{
		myEngine.ObjectsCollide(&circleBody1, &circleBody2);
		myEngine.ObjectsCollide(&circleBody1, &circleBody2);
		myEngine.ObjectsCollide(&SquareBody1, &SquareBody2);
	}
}
BENCHMARK(BM_OptimizedSAT_RequiredToSAT_SqToSq);

static void BM_OptimizedSAT_RequiredToSAT_SqToCi(benchmark::State& state)
{
	for (auto _ : state)
	{
		myEngine.ObjectsCollide(&circleBody1, &circleBody2);
		myEngine.ObjectsCollide(&circleBody1, &circleBody2);
		myEngine.ObjectsCollide(&circleBody1, &SquareBody2);
	}
}
BENCHMARK(BM_OptimizedSAT_RequiredToSAT_SqToCi);
BENCHMARK_MAIN();