#pragma once
#include "RigidBody.h"
#include <algorithm>
#include <ranges>

#ifdef TRACY_ENABLE
#include <tracy/Tracy.hpp>
#endif

class KdTree
{
public:
	struct KdNode
	{
		KdNode* parent = nullptr;
		KdNode* childLeft = nullptr;
		KdNode* childRight = nullptr;

		int depth = 0;
		bool divideIsX = true;
		float division = 0;

		std::vector<std::pair<float, float>> myTempPoints;
		std::vector<int> indexOfNodeBodies;

		KdNode() = default;

		void InsertSplitPosVec(std::vector<std::pair<float, float>> pos)
		{
			myTempPoints = pos;
			if (divideIsX)
			{
				std::ranges::sort(myTempPoints, {}, &std::pair<float, float>::first);
				return;
			}
			std::ranges::sort(myTempPoints, {}, &std::pair<float, float>::second);

		}

		void SortBasedOnDivX()
		{
#ifdef TRACY_ENABLE
			ZoneScoped;
#endif
			if (divideIsX)
			{
				std::ranges::sort(myTempPoints, {}, &std::pair<float, float>::first);
			}
			else
			{
				std::ranges::sort(myTempPoints, {}, &std::pair<float, float>::second);
			}
		}

		void GenerateNodeFromParent(KdNode Parent, bool rightChild)
		{
#ifdef TRACY_ENABLE
			ZoneScoped;
#endif
			parent = &Parent;
			depth = parent->depth + 1;
			if (parent->divideIsX)
			{
				divideIsX = false;
			}

			auto middle = parent->myTempPoints.size() / 2;

			if (rightChild)
			{
				for (auto myPoint = parent->myTempPoints.begin() + middle; myPoint != parent->myTempPoints.end(); myPoint++)
				{
					myTempPoints.emplace_back(*myPoint);
				}
				parent->childRight = this;
			}
			else
			{
				testFn(middle);
				parent->childLeft = this;
			}
			SortBasedOnDivX();
			division = myTempPoints.at(myTempPoints.size() / 2).first;
			myTempPoints.erase(myTempPoints.begin() + myTempPoints.size() / 2);
		}
		void testFn(long long middle)
		{
#ifdef TRACY_ENABLE
			ZoneScoped;
#endif
			for (auto myPoint = parent->myTempPoints.begin(); myPoint != parent->myTempPoints.begin() + middle; myPoint++)
			{

				myTempPoints.emplace_back(*myPoint);
			}
		}
	};
private:
	// For reverse iteration
	std::vector<std::unique_ptr<KdNode>> nodes_;

	const std::vector<RigidBody*>* engineRB_;

	// For test
	int elemSize = 0;
	int frameStop = 0;
public:

	KdTree() = default;

	void ResetTree()
	{
		nodes_.clear();
	}

	void Init(const std::vector<RigidBody*>& bodyList)
	{
#ifdef TRACY_ENABLE
		ZoneScoped;
#endif
		if (frameStop == 0)
		{
			frameStop = 0;
			if (bodyList.size() != 0)
			{
				engineRB_ = &bodyList;
				std::vector<std::pair<float, float>> temp;
				elemSize = bodyList.size();
				//std::cout << elemSize << std::endl;
				for (auto body : bodyList)
				{
					temp.emplace_back(body->getPosition().X(), body->getPosition().Y());
				}
				std::ranges::sort(temp, {}, &std::pair<float, float>::first);
				float xDiff = temp.at(0).first - temp.at(temp.size() - 1).first;
				auto temp2 = temp;
				std::ranges::sort(temp2, {}, &std::pair<float, float>::second);
				float yDiff = temp2.at(0).second - temp.at(temp2.size() - 1).second;


				nodes_.emplace_back(new KdNode);
				auto rootNode = nodes_.at(0).get();
				rootNode->depth = 1;
				rootNode->divideIsX = xDiff > yDiff;

				rootNode->myTempPoints.reserve(temp.size());

				if (rootNode->divideIsX)
				{
					rootNode->division = temp.at(temp.size() / 2).first;
					temp.erase(temp.begin() + temp.size() / 2);
					rootNode->myTempPoints = std::move(temp);
				}
				else
				{
					rootNode->division = temp2.at(temp2.size() / 2).first;
					temp2.erase(temp2.begin() + temp2.size() / 2);
					rootNode->myTempPoints = std::move(temp2);
				}
				GenerateTree();
			}
		}
		frameStop;
	}

	void GenerateTree()
	{
#ifdef TRACY_ENABLE
		ZoneScoped;
#endif
		int i = 0;
		auto myNode = nodes_.at(0).get();

		/*int passNum;
		int rbNum;
		while (rbNum > 7)
		{
			rbNum /= 2;
			++passNum;
		}*/

		while (i != nodes_.size())
		{
			if (myNode->depth > 4)
				break;
			if (myNode->myTempPoints.size() >= 7)
			{
				//std::cout << elemSize<< " " << myNode->depth << std::endl;
				KdNode* newNodeRight = new KdNode;
				KdNode* newNodeLeft = new KdNode;
				newNodeRight->GenerateNodeFromParent(*myNode, true);
				newNodeLeft->GenerateNodeFromParent(*myNode, false);
				nodes_.emplace_back(newNodeLeft);
				nodes_.emplace_back(newNodeRight);
			}
			myNode = nodes_.at(i).get();
			i++;


		}
	}

	bool EmplacementBasedOnAxis(KdNode newNode) const
	{
		if (nodes_.at(0)->divideIsX)
		{
			return newNode.depth % 2;
		}
		if (!nodes_.at(0)->divideIsX)
		{
			return !(newNode.depth % 2);
		}
		std::cout << "Warning : node dimension invalid" << std::endl;
		return false;
	}

	void InsertRb(RigidBody* body, int index)
	{
		std::pair<Vector2D, Vector2D> AABB = body->getCollider()->ReturnAABBCollider();
		auto myNode = nodes_.at(0).get();
		float min = AABB.first.Y();
		float max = AABB.second.Y();
		while (myNode->childRight != nullptr && myNode->childLeft != nullptr)
		{
			float min = AABB.first.Y();
			float max = AABB.second.Y();
			if (myNode->parent->divideIsX)
			{
				float min = AABB.first.X();
				float max = AABB.second.X();
			}
			// RIGHT
			if (min > myNode->division && max > myNode->division)
			{
				myNode = myNode->childRight;
			}
			// LEFT
			else if (min < myNode->division && max < myNode->division)
			{
				myNode = myNode->childLeft;
			}
			else
			{
				myNode->indexOfNodeBodies.emplace_back(index);
			}
		}
	}
};