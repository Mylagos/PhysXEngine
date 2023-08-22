#pragma once
#include "benchmark/benchmark.h"
#include "../Engine/include/KdTree.h"
#include "../Engine/include/RectCollider.h"
#include "../Engine/include/Engine.h"
#include <deque>
#include <thread>
#include <vector>
#include <functional>
#include <mutex>
#include <condition_variable>
#ifdef TRACY_ENABLE
#include <tracy/Tracy.hpp>
#endif

struct myBodyList
{
	std::vector<RigidBody*> bodyList;

	myBodyList(int number)
	{
		for (int i = 0; i < number; i++)
		{
			//auto body = new RigidBody(Vector2D(static_cast<float>(i*50), static_cast<float>(i*50)), 50);
			auto body = new RigidBody(Vector2D(static_cast<float>(i), static_cast<float>(i)), Vector2D(0.1f, 0.1f));
			bodyList.emplace_back(body);
		}
	}
};

class JobSystem {
public:
    JobSystem(int numThreads) : stop(false) {
        for (int i = 0; i < numThreads; ++i) {
            threads.emplace_back(&JobSystem::WorkerThread, this);
        }
    }

    ~JobSystem() {
        {
            std::unique_lock<std::mutex> lock(queueMutex);
            stop = true;
        }
        condition.notify_all();

        for (std::thread& thread : threads) {
            thread.join();
        }
    }

    void AddJob(std::function<void()> job) {
        std::unique_lock<std::mutex> lock(queueMutex);
        jobQueue.push_back(job);
        condition.notify_one();
    }

private:
    void WorkerThread() {
        while (true) {
            std::function<void()> job;

            {
                std::unique_lock<std::mutex> lock(queueMutex);
                condition.wait(lock, [this] { return stop || !jobQueue.empty(); });
                if (stop && jobQueue.empty()) {
                    return;
                }
                job = jobQueue.front();
                jobQueue.pop_front();
            }

            job();
        }
    }

    std::vector<std::thread> threads;
    std::deque<std::function<void()>> jobQueue;
    std::mutex queueMutex;
    std::condition_variable condition;
    bool stop;
};

int main()
{
    const int numThreads = std::thread::hardware_concurrency();
    JobSystem jobSystem(numThreads);
	myBodyList bodyList1(10);
	KdTree kdTree;
	kdTree.ResetTree();
	kdTree.InitOpti(bodyList1.bodyList);
	int i = 0;
	for (auto& body : bodyList1.bodyList)
	{
		kdTree.InsertRbOpti(*body, i);
		i++;
	}
    auto kdCol = [](RigidBody* body1, RigidBody* body2)
	{
        std::cout << Engine::ObjectsCollide(body1, body2) << std::endl;
    };
	while (true)
    {
        std::vector<std::pair<int, int>> collisions = kdTree.GetCollisions();

        for (auto& [firstId, secondId] : collisions)
        {
            RigidBody*& body1 = bodyList1.bodyList.at(firstId);
            RigidBody*& body2 = bodyList1.bodyList.at(secondId);
            jobSystem.AddJob(std::bind(kdCol, body1, body2));
        }
    }

	return EXIT_SUCCESS;
}