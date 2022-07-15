#pragma once

#include "RigidBody.h"
#include <algorithm>
#include <map>
#include <queue>
#include <stack>

class KdNode
{
private:
	KdNode* parent_;
	std::unique_ptr<KdNode> childLeftDown_;
	std::unique_ptr<KdNode> childRightUp_;

	std::vector<Vector2D> pointList_;

	float divider_;
	int kdLayer_ = 0;
	int pointsNumber_ = pointList_.size();


	std::vector<RigidBody*> kdBodyList_;

public:

	KdNode();
	KdNode(KdNode*);

	void EmplacePoint(Vector2D vec)
	{
		float point;
		if (kdLayer_ %2 == 0)
			point = vec.X();
		if(kdLayer_ % 2 == 1)
			point = vec.Y();
		if (point >= divider_)
		{
			childRightUp_->EmplacePoint(vec);
			return;
		}
		childRightUp_->EmplacePoint(vec);
		return;
	}



	KdNode* getParent() { return parent_; }
	void addPointToList(Vector2D);
	std::vector<Vector2D> getPointList() { return pointList_; }
	int getNumberOfPoints() { return pointsNumber_; }
};



class KdTree
{
private:
	int k_ = 2;
	int currentLayer_ = 0;
	
	std::vector<Vector2D> pointList_;
	std::queue<KdNode> kdNodesQueue_;

public:

	int Axis() const { return currentLayer_ % k_; }



	void sortPointList(const std::vector<RigidBody*>& engineRb)
	{
		pointList_.clear();

		Vector2D pointsAverage;
		for (auto& rb : engineRb)
		{
			pointsAverage += rb->getPosition();
			pointList_.emplace_back(rb->getPosition());
		}

		pointsAverage / (engineRb.size() + 1);

		std::sort(pointList_.begin(), pointList_.end(), [pointsAverage](Vector2D a, Vector2D b)
			{ return a < pointsAverage; }
		);
	}

	



	//void generateTree(const std::vector<RigidBody*>&);
	//static bool FirstDivisionIsX(Vector2D);

	//std::pair<int, float> CreateConditions(Vector2D);
	//static bool DivisionIsX(int);
	//static bool NumberGreater(float, float);

	//void GenerateRootNode();
	//void GenerateNode();
	//void SortBodies();
};
