#pragma once
#include "benchmark/benchmark.h"
#include "../Engine/include/Engine.h"


RigidBody circleBody1 = RigidBody(Vector2D(1.0f, 1.0f), 25.0f, 0.0f);
RigidBody circleBody2 = RigidBody(Vector2D(1.1f, 1.1f), 25.0f, 0.0f);
RigidBody SquareBody1 = RigidBody(Vector2D(1.1f, 1.1f), Vector2D(25.0f, 25.0f), 0.0f, 0.0f);
RigidBody SquareBody2 = RigidBody(Vector2D(1.0f, 1.0f), Vector2D(25.0f, 25.0f), 0.0f, 25.0f);

Engine myEngine;

RectCollider* rectCol1 = dynamic_cast<RectCollider*>(SquareBody1.getCollider());
RectCollider* rectCol2 = dynamic_cast<RectCollider*>(SquareBody2.getCollider());
Vector2D axis1 = Vector2D(rectCol2->ReturnPoints().at(0) - rectCol2->ReturnPoints().at(1));
Vector2D axis2 = Vector2D(rectCol2->ReturnPoints().at(0) - rectCol2->ReturnPoints().at(1));

static void BM_OrthoRight(benchmark::State& state)
{
	for (auto _ : state)
	{
		Vector2D(1.0f, 2.0f).OrthoRight();
	}

}
BENCHMARK(BM_OrthoRight);

static void BM_SAT_Sandbox(benchmark::State& state)
{
	for (auto _ : state)
	{
		std::vector<Vector2D> axises;
		axises = Collider::SatAxes(
			Vector2D(rectCol2->ReturnPoints().at(0) - rectCol2->ReturnPoints().at(1)),
			Vector2D(rectCol2->ReturnPoints().at(0) - rectCol2->ReturnPoints().at(1)));
		for (const auto& axis : axises)
		{
			float tempMTV;
			Collider::SAT(axis, rectCol1->ReturnPoints(), rectCol2->ReturnPoints(), tempMTV);

		}
	}

}
BENCHMARK(BM_SAT_Sandbox);
static void BM_SAT_Sandbox2(benchmark::State& state)
{

	for (auto _ : state)
	{
		std::vector<Vector2D> axises;
		axises = Collider::SatAxesOpti(
			Vector2D(rectCol2->ReturnPointsOpti().at(0) - rectCol2->ReturnPointsOpti().at(1)),
			Vector2D(rectCol2->ReturnPointsOpti().at(0) - rectCol2->ReturnPointsOpti().at(1)));
		for (const auto& axis : axises)
		{
			float tempMTV;
			Collider::SAT(axis, rectCol1->ReturnPointsOpti(), rectCol2->ReturnPointsOpti(), tempMTV);

		}
	}

}
BENCHMARK(BM_SAT_Sandbox2);
static void BM_SAT_Sandbox3(benchmark::State& state)
{
	for (auto _ : state)
	{
		std::vector<Vector2D> returnAxes;
		returnAxes.emplace_back(axis1.OrthoLeft());
		returnAxes.emplace_back(axis1);
		returnAxes.emplace_back(axis1.OrthoRight());
		returnAxes.emplace_back(-axis1);
		returnAxes.emplace_back(axis2.OrthoLeft());
		returnAxes.emplace_back(axis2);
		returnAxes.emplace_back(axis2.OrthoRight());
		returnAxes.emplace_back(-axis2);
	}

}
BENCHMARK(BM_SAT_Sandbox3);

static void BM_GenerateAxesSAT_Optimized3(benchmark::State& state)
{
	for (auto _ : state)
	{
		std::vector<Vector2D> axises;
		axises = Collider::SatAxesOpti(
			Vector2D(rectCol2->rectRotatedPoints_.at(0) - rectCol2->rectRotatedPoints_.at(1)),
			Vector2D(rectCol2->rectRotatedPoints_.at(0) - rectCol2->rectRotatedPoints_.at(1)));
	}

}


static void BM_GenerateAxesSAT(benchmark::State& state)
{
	for (auto _ : state)
	{
		std::vector<Vector2D> axises;
		axises = Collider::SatAxes(
			Vector2D(rectCol2->ReturnPoints().at(0) - rectCol2->ReturnPoints().at(1)),
			Vector2D(rectCol2->ReturnPoints().at(0) - rectCol2->ReturnPoints().at(1)));
	}

}
BENCHMARK(BM_GenerateAxesSAT);

static void BM_GenerateAxesSAT_Optimized(benchmark::State& state)
{
	for (auto _ : state)
	{
		std::vector<Vector2D> axises;
		axises = Collider::SatAxesOpti(
			Vector2D(rectCol2->ReturnPoints().at(0) - rectCol2->ReturnPoints().at(1)),
			Vector2D(rectCol2->ReturnPoints().at(0) - rectCol2->ReturnPoints().at(1)));
	}

}
BENCHMARK(BM_GenerateAxesSAT_Optimized);

static void BM_GenerateAxesSAT_Optimized2(benchmark::State& state)
{
	for (auto _ : state)
	{
		std::vector<Vector2D> axises;
		axises = Collider::SatAxesOpti(
			Vector2D(rectCol2->ReturnPointsOpti().at(0) - rectCol2->ReturnPointsOpti().at(1)),
			Vector2D(rectCol2->ReturnPointsOpti().at(0) - rectCol2->ReturnPointsOpti().at(1)));
	}
}
BENCHMARK(BM_GenerateAxesSAT_Optimized2);
