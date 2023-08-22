#include "VisualWorld.h"

//struct myBodyList
//{
//	std::vector<RigidBody*> bodyList;
//
//	myBodyList(int number)
//	{
//		for (int i = 0; i < number; i++)
//		{
//			//bodyList.emplace_back(new RigidBody(Vector2D(static_cast<float>(i), static_cast<float>(i)), Vector2D(1.0f, 1.0f)));
//			auto body = new RigidBody(Vector2D(static_cast<float>(i), static_cast<float>(i)), Vector2D(1.0f, 1.0f));
//			bodyList.emplace_back(body);
//		}
//	}
//};

int main()
{
	/*myBodyList bodyList1(1500);
	KdTree kdTree;
	kdTree.InitOpti(bodyList1.bodyList);
	int i = 0;
	for (auto& body : bodyList1.bodyList)
	{
		kdTree.InsertRbOpti(body);
		++i;
	}
	kdTree.PrintTree();*/
	VisualWorld world;
	world.WorldLoop();
	return EXIT_SUCCESS;
}