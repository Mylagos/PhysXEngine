#pragma once
#include "RigidBody.h"
#include <algorithm>
#include <ranges>
#include <unordered_map>

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

		int thisNodeIdx = 0;
		int depth = 0;
		int myElemNum = 0;
		bool divideIsX = true;
		float division = 0;

		std::vector<std::pair<float, float>> myTempPoints;
		std::vector<int> indexOfNodeBodies;
		std::vector<RigidBody*> nodeBodyList;

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
				myTempPoints.resize(middle);
				for (int i = middle; i < middle / 2; ++i)
				{
					myTempPoints.at(i - middle) = parent->myTempPoints.at(i);
				}
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
		void GenerateNodeFromParentOpti(KdNode& Parent, bool rightChild)
		{
#ifdef TRACY_ENABLE
			ZoneScoped;
#endif
			parent = &Parent;
			depth = parent->depth + 1;
			float xmax = FLT_MIN;
			float xmin = FLT_MAX;
			float xmoy = 0.0f;

			float ymax = FLT_MIN;
			float ymin = FLT_MAX;
			float ymoy = 0.0f;

			for(int i = 0; i < parent->myElemNum; i++)
			{
				if (xmax < parent->myTempPoints.at(i).first)
				{
					xmax = parent->myTempPoints.at(i).first;
				}
				if (xmin > parent->myTempPoints.at(i).first)
				{
					xmin = parent->myTempPoints.at(i).first;
				}
				xmoy += parent->myTempPoints.at(i).first;

				if (ymax < parent->myTempPoints.at(i).second)
				{
					ymax = parent->myTempPoints.at(i).second;
				}
				if (ymin > parent->myTempPoints.at(i).second)
				{
					ymin = parent->myTempPoints.at(i).second;
				}
				ymoy += parent->myTempPoints.at(i).second;
			}

			xmoy /= parent->myElemNum;
			ymoy /= parent->myElemNum;

			float xDiff = xmin - xmax;
			float yDiff = ymin - ymax;
			divideIsX = std::abs(xDiff) > std::abs(yDiff);

			myTempPoints.resize(parent->myElemNum);
			//float moy = 0.0f;
			//if (divideIsX)
			//{
			//	for (auto pos : parent->myTempPoints)
			//	{
			//		moy += pos.first;
			//	}
			//}
			//if (!divideIsX)
			//{
			//	for (auto pos : parent->myTempPoints)
			//	{
			//		moy += pos.second;
			//	}
			//}
			//moy /= parent->myTempPoints.size();
			int i = 0;
			float myDivide = 0.0f;
			if (rightChild && divideIsX)
			{
				for (int j = 0; j < parent->myElemNum; j++)
				{
					if (parent->myTempPoints.at(j).first > xmoy)
					{
						myElemNum++;
						myTempPoints.at(i) = parent->myTempPoints.at(j);
						myDivide += parent->myTempPoints.at(j).first;
						i++;
					}
				}
				parent->childRight = this;
			}
			if (rightChild && !divideIsX)
			{
				for (int j = 0; j < parent->myElemNum; j++)
				{
					if (parent->myTempPoints.at(j).second > ymoy)
					{
						myElemNum++;
						myTempPoints.at(i) = parent->myTempPoints.at(j);
						myDivide += parent->myTempPoints.at(j).second;
						i++;
					}
				}
				parent->childRight = this;
			}
			if (!rightChild && divideIsX)
			{
				for (int j = 0; j < parent->myElemNum; j++)
				{
					if (parent->myTempPoints.at(j).first < xmoy)
					{
						myElemNum++;
						myTempPoints.at(i) = parent->myTempPoints.at(j);
						myDivide += parent->myTempPoints.at(j).first;
						i++;
					}
				}
				parent->childLeft = this;
			}
			if (!rightChild && !divideIsX)
			{
				for (int j = 0; j < parent->myElemNum; j++)
				{
					if (parent->myTempPoints.at(j).second < xmoy)
					{
						myElemNum++;
						myTempPoints.at(i) = parent->myTempPoints.at(j);
						myDivide += parent->myTempPoints.at(j).second;
						i++;
					}
				}
				parent->childLeft = this;
			}
			division = myDivide /= myTempPoints.size();
		}
		void testFn(long long middle)
		{
#ifdef TRACY_ENABLE
			ZoneScoped;
#endif
			myTempPoints.resize(middle);
			for (int i = 0; i < middle; ++i)
			{
				myTempPoints.at(i) = parent->myTempPoints.at(i);
			}
		}
	};
private:
	// For reverse iteration
	std::vector<std::unique_ptr<KdNode>> nodes_;

	std::vector<RigidBody*> engineRB_;

	// For test
	int elemSize = 0;
	int frameStop = 0;
public:

	std::vector<std::pair<int, int>> possibleCollisions_;
	std::vector<std::pair<RigidBody*, RigidBody*>> collisionPair;
	std::unordered_multimap<int, int> possibleCollisionsMap_;
	


	KdTree() = default;

	void ResetTree()
	{
		nodes_.clear();
	}
	void PrintTree()
	{
		int ret = 0;
		for (int i = 0; i<nodes_.size(); i++)
		{
			std::cout << "Node : " << i << ". layer : " << nodes_.at(i)->depth << ". NbOfElements : " << nodes_.at(i)->indexOfNodeBodies.size() << ".\n";
			ret += nodes_.at(i)->indexOfNodeBodies.size();
		}
		std::cout << "Total of sorted elements " << ret << std::endl;
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
				
				int a = 0;
				engineRB_.resize(bodyList.size());
				for (RigidBody* body : bodyList)
				{
					RigidBody* newBody = new RigidBody(*body);
					engineRB_.at(a) = (newBody);
					a++;
				}
				std::vector<std::pair<float, float>> temp;
				elemSize = bodyList.size();

				InitTestEmplace(temp);

				TestSort(temp);
				float xDiff = temp.at(0).first - temp.at(temp.size() - 1).first;

				auto temp2 = temp;
				TestSort2(temp2);
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
					TestGenerateFirstChild(rootNode, temp2);
				}
				GenerateTree();
			}
		}
		frameStop;
	}

	void InitOpti(const std::vector<RigidBody*> bodyList)
	{
#ifdef TRACY_ENABLE
		ZoneScoped;
#endif
		if (frameStop == 0)
		{
			frameStop = 0;
			if (bodyList.size() != 0)
			{
				int a = 0;
				std::vector<RigidBody*> ooo;
				ooo.resize(bodyList.size());
				for (RigidBody* body : bodyList)
				{
					RigidBody* newBody = new RigidBody(*body);
					ooo.at(a) = (newBody);
					a++;
				}
				std::vector<std::pair<float, float>> temp(ooo.size());
				int i = 0;
				for (int i = 0; i < ooo.size(); ++i)
				{
					temp.at(i) = std::make_pair(ooo.at(i)->getPosition().X(), ooo.at(i)->getPosition().Y());
				}

				float xmin = FLT_MAX;
				float xmax = FLT_MIN;
				float xmoy = 0.0f;

				float ymin = FLT_MAX;
				float ymax = FLT_MIN;
				float ymoy = 0.0f;

				for (auto p : temp)
				{
					if (xmin > p.first)
					{
						xmin = p.first;
					}
					if (xmax < p.first)
					{
						xmax = p.first;
					}
					xmoy += p.first;

					if (ymin > p.second)
					{
						ymin = p.second;
					}
					if (ymax < p.second)
					{
						ymax = p.second;
					}
					ymoy += p.second;
				}

				float xDiff = xmin - xmax;
				float yDiff = ymin - ymax;
				xmoy /= temp.size();
				ymoy /= temp.size();


				nodes_.emplace_back(new KdNode);
				auto rootNode = nodes_.at(0).get();
				rootNode->myElemNum = temp.size();
				rootNode->depth = 1;
				rootNode->divideIsX = std::abs(xDiff) > std::abs(yDiff);

				rootNode->myTempPoints.resize(temp.size());

				if (rootNode->divideIsX)
				{
					rootNode->division = xmoy;
				}
				else
				{
					rootNode->division = ymoy;
				}
				rootNode->myTempPoints = std::move(temp);
				GenerateTreeOpti();
			}
		}
		frameStop;
	}

	void InitTestEmplace(std::vector<std::pair<float, float>>& temp)
	{
#ifdef TRACY_ENABLE
		ZoneScoped;
#endif
		temp.resize(elemSize);
		for (int i = 0; i < elemSize; ++i)
		{
			temp.at(i) = std::make_pair(engineRB_.at(i)->getPosition().X(), engineRB_.at(i)->getPosition().Y());
		}
	}

	void TestGenerateFirstChild(KdNode* rootNode, std::vector<std::pair<float, float>> temp2)
	{
#ifdef TRACY_ENABLE
		ZoneScoped;
#endif
		rootNode->division = temp2.at(temp2.size() / 2).first;
		temp2.erase(temp2.begin() + temp2.size() / 2);
		rootNode->myTempPoints = std::move(temp2);
	}

	void TestSort(std::vector<std::pair<float, float>>& temp)
	{
#ifdef TRACY_ENABLE
		ZoneScoped;
#endif
		std::ranges::sort(temp, {}, &std::pair<float, float>::first);
	}

	void TestSort2(std::vector<std::pair<float, float>>& temp2)
	{
#ifdef TRACY_ENABLE
		ZoneScoped;
#endif
		std::ranges::sort(temp2, {}, &std::pair<float, float>::first);
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
			if (myNode->depth > 3)
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
	void GenerateTreeOpti()
	{
#ifdef TRACY_ENABLE
		ZoneScoped;
#endif
		int i = 0;

		/*int passNum;
		int rbNum;
		while (rbNum > 7)
		{
			rbNum /= 2;
			++passNum;
		}*/
		int totalNodes = 0;
		nodes_.at(i)->thisNodeIdx = totalNodes;
		totalNodes++;
		bool loop = true;
		while (loop)
		{
			if(i > nodes_.size()-1)
			{
				break;
			}
			auto myNode = nodes_.at(i).get();
			if (myNode->depth > 20)
				break;
			if (myNode->myElemNum >= 7)
			{
				//std::cout << elemSize<< " " << myNode->depth << std::endl;
				KdNode* newNodeRight = new KdNode;
				KdNode* newNodeLeft = new KdNode;
				newNodeRight->GenerateNodeFromParentOpti(*myNode, true);
				newNodeLeft->GenerateNodeFromParentOpti(*myNode, false);
				newNodeLeft->thisNodeIdx = totalNodes;
				totalNodes++;
				nodes_.emplace_back(newNodeLeft);
				newNodeRight->thisNodeIdx = totalNodes;
				totalNodes++;
				nodes_.emplace_back(newNodeRight);
			}
			i++;
		}
		int ia = 0;
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
#ifdef TRACY_ENABLE
		ZoneScoped;
#endif
		const std::pair<Vector2D, Vector2D> AABB = body->getCollider()->ReturnAABBCollider();
		auto myNode = nodes_.at(0).get();
		bool loop = true;
		while (loop)
		{
			float min = AABB.first.Y();
			float max = AABB.second.Y();

			if (myNode->divideIsX)
			{
				float min = AABB.first.X();
				float max = AABB.second.X();
			}


			// RIGHT
			if (min > myNode->division && max > myNode->division && myNode->childRight)
			{
				myNode = myNode->childRight;
			}
			// LEFT
			else if (min < myNode->division && max < myNode->division && myNode->childLeft)
			{
				myNode = myNode->childLeft;
			}
			else
			{
				myNode->nodeBodyList.emplace_back(body);
				myNode->indexOfNodeBodies.emplace_back(index);
				loop = false;
			}
		}
	}
	void InsertRbOpti(RigidBody body, int index)
	{
#ifdef TRACY_ENABLE
		ZoneScoped;
#endif
		const std::pair<Vector2D, Vector2D> AABB = body.getCollider()->ReturnAABBCollider();
		auto myNode = nodes_.at(0).get();
		bool loop = true;
		while (loop)
		{
			bool switched = false;
			float min = AABB.first.Y();
			float max = AABB.second.Y();

			if (myNode->divideIsX)
			{
				min = AABB.first.X();
				max = AABB.second.X();
			}


			// RIGHT
			if(myNode->childRight)
			{
				if (min > myNode->division && max > myNode->division)
				{
					//std::cout << "eee\n";
					myNode = myNode->childRight;
					switched = true;
				}
			}

			// LEFT
			if(myNode->childLeft)
			{
				if (min < myNode->division && max < myNode->division)
				{
					//std::cout << "ooo\n";
					myNode = myNode->childLeft;
					switched = true;
				}
			}

			if (!switched)
			{
				//myNode->nodeBodyList.emplace_back(body);
				myNode->indexOfNodeBodies.emplace_back(index);
				//std::cout << myNode->indexOfNodeBodies.size() << std::endl;
				loop = false;
			}
		}
	}
	void ReturnCollisions()
	{
		//possibleCollisions_.resize(15000);
		int idx = 0;
		for (int i = nodes_.size()-1; i > -1; i--)
		{
			KdNode* myNode = nodes_.at(i).get();
			if (myNode->indexOfNodeBodies.size() == 0)
				continue;
			for(int a = 0; a < myNode->indexOfNodeBodies.size(); a++)
			{
				auto parent = myNode;
				while (parent)
				{
					if (parent->indexOfNodeBodies.size() == 0)
					{
						if (parent->parent)
						{
							parent = parent->parent;
						}
						else
							break;
						continue;
					}
					for (int b = 0; b < parent->indexOfNodeBodies.size(); b++)
					{
						possibleCollisions_.emplace_back(std::make_pair(myNode->indexOfNodeBodies.at(a), parent->indexOfNodeBodies.at(b)));
						collisionPair.emplace_back(std::make_pair(myNode->nodeBodyList.at(a), parent->nodeBodyList.at(b)));
						//possibleCollisions_.at(idx) = std::make_pair(myNode->indexOfNodeBodies.at(a), parent->indexOfNodeBodies.at(b));
						idx++;
					}
					if (parent->parent)
					{
						parent = parent->parent;
					}
					else
						break;
				}
			}
		}
		int ooo;
	}
	std::vector<std::pair<int, int>> GetCollisions()
	{
#ifdef TRACY_ENABLE
		ZoneScoped;
#endif
		//possibleCollisions_.resize(15000);

		std::vector<std::pair<int, int>> collisions;
		int idx = 0;
		for (int i = nodes_.size()-1; i > -1; i--)
		{
			KdNode* myNode = nodes_.at(i).get();
			//std::cout << "Checking Node " << i << " NbOfElem " << myNode->indexOfNodeBodies.size() << std::endl;
			if (myNode->indexOfNodeBodies.size() == 0)
				continue;
			for (int a = 0; a < myNode->indexOfNodeBodies.size(); a++)
			{
				bool firstIter = true;
				//int j = 0;
				auto parent = myNode;
				while (parent)
				{
					if (parent->indexOfNodeBodies.size() == 0)
					{
						if (parent->parent)
						{
							parent = parent->parent;
						}
						else
							break;
						continue;
					}
					for (int b = 0; b < parent->indexOfNodeBodies.size(); b++)
					{
						if(firstIter)
						{
							firstIter = false;
							b = a + 1;
							if(b > parent->indexOfNodeBodies.size()-1)
							{
								break;
							}
						}
						collisions.emplace_back(myNode->indexOfNodeBodies.at(a), parent->indexOfNodeBodies.at(b));
						//possibleCollisions_.at(idx) = std::make_pair(myNode->indexOfNodeBodies.at(a), parent->indexOfNodeBodies.at(b));
						//std::cout << "Collision : Node " << i << ". Rb " << myNode->indexOfNodeBodies.at(a) << ". Parent " << a << ".Rb " << parent->indexOfNodeBodies.at(b) << std::endl;
						//std::cout << "I : " << i << " A :  " << a << " B : " << b << std::endl;
						idx++;
					}
					if (parent->parent)
					{
						parent = parent->parent;
					}
					else
					{
						//j++;
						break;
					}

				}
			}
		}
		int ooo;
		return collisions;
	}
	void GetCollisionsVoid()
	{
#ifdef TRACY_ENABLE
		ZoneScoped;
#endif
		//possibleCollisions_.resize(15000);

		std::vector<std::pair<int, int>> collisions;
		int idx = 0;
		for (int i = nodes_.size() - 1; i > -1; i--)
		{
			KdNode* myNode = nodes_.at(i).get();
			std::cout << "Checking Node " << i << " NbOfElem " << myNode->indexOfNodeBodies.size() << std::endl;
			if (myNode->indexOfNodeBodies.size() == 0)
				continue;
			for (int a = 0; a < myNode->indexOfNodeBodies.size(); a++)
			{
				bool firstIter = true;
				//int j = 0;
				auto parent = myNode;
				while (parent)
				{
					if (parent->indexOfNodeBodies.size() == 0)
					{
						if (parent->parent)
						{
							parent = parent->parent;
						}
						else
							break;
						continue;
					}
					for (int b = 0; b < parent->indexOfNodeBodies.size(); b++)
					{
						if (firstIter)
						{
							firstIter = false;
							b = a + 1;
							if (b > parent->indexOfNodeBodies.size() - 1)
							{
								break;
							}
						}
						collisions.emplace_back(myNode->indexOfNodeBodies.at(a), parent->indexOfNodeBodies.at(b));
						//possibleCollisions_.at(idx) = std::make_pair(myNode->indexOfNodeBodies.at(a), parent->indexOfNodeBodies.at(b));
						//std::cout << "Collision : Node " << i << ". Rb " << myNode->indexOfNodeBodies.at(a) << ". Parent " << a << ".Rb " << parent->indexOfNodeBodies.at(b) << std::endl;
						//std::cout << "I : " << i << " A :  " << a << " B : " << b << std::endl;
						idx++;
					}
					if (parent->parent)
					{
						parent = parent->parent;
					}
					else
					{
						//j++;
						break;
					}

				}
			}
		}
	}
	void ReturnCollisionsMap()
	{
		//possibleCollisions_.resize(15000);
		int idx = 0;
		for (int i = nodes_.size() - 1; i > -1; i--)
		{
			KdNode* myNode = nodes_.at(i).get();
			if (myNode->indexOfNodeBodies.size() == 0)
				continue;
			for (int a = 0; a < myNode->indexOfNodeBodies.size() - 1; a++)
			{
				auto parent = myNode;
				while (parent)
				{
					if (parent->indexOfNodeBodies.size() == 0)
					{
						if (parent->parent)
						{
							parent = parent->parent;
						}
						else
							break;
						continue;
					}
					for (int b = 0; b < parent->indexOfNodeBodies.size() - 1; b++)
					{
						possibleCollisionsMap_.insert({ myNode->indexOfNodeBodies.at(a), parent->indexOfNodeBodies.at(b)});
						//possibleCollisions_.at(idx) = std::make_pair(myNode->indexOfNodeBodies.at(a), parent->indexOfNodeBodies.at(b));
						idx++;
					}
					if (parent->parent)
					{
						parent = parent->parent;
					}
					else
						break;
				}
			}
		}
	}
	void EmptyCollisionsMap()
	{
		possibleCollisionsMap_.clear();
	}
	void EmptyCollisions()
	{
		possibleCollisions_.clear();
		collisionPair.clear();
	}
};