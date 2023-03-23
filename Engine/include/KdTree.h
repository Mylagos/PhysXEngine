#pragma once
#include "RigidBody.h"

#ifdef TRACY_ENABLE
#include <tracy/Tracy.hpp>
#endif

#include <algorithm>
class KdTree
{
public:
	struct KdNode
	{
		KdNode* parent = nullptr;
		KdNode* childLeft = nullptr;
		KdNode* chlidRight = nullptr;
		int depth = 0;
		bool divideIsX = true;
		float division = 0;
		std::vector<std::pair<float, float>> myTempPoints{};

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
				parent->chlidRight = this;
			}
			else
			{
				for (auto myPoint = parent->myTempPoints.begin(); myPoint != parent->myTempPoints.begin() + middle; myPoint++)
				{
					myTempPoints.emplace_back(*myPoint);
				}
				parent->childLeft = this;
			}
			SortBasedOnDivX();
			division = myTempPoints.at(myTempPoints.size() / 2).first;
			myTempPoints.erase(myTempPoints.begin() + myTempPoints.size() / 2);
		}
	};
private:
	std::vector<KdNode*> nodes_;
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
		if (frameStop == 50)
		{
			frameStop = 0;
			if (bodyList.size() != 0)
			{

				std::vector<std::pair<float, float>> temp;
				elemSize = bodyList.size();
				std::cout << elemSize << std::endl;
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
				auto rootNode = nodes_.at(0);
				rootNode->depth = 1;
				rootNode->divideIsX = xDiff > yDiff;

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
		frameStop++;
	}

	void GenerateTree()
	{
#ifdef TRACY_ENABLE
		ZoneScoped;
#endif
		int i = 0;
		auto myNode = nodes_.at(0);
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
			myNode = nodes_.at(i);
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
};