#include "BSP.h"
//
//void KdTree::generateTree(const std::vector<RigidBody*>& engineRb)
//{
//	kdPointList_.clear();
//
//	Vector2D pointsAverage;
//
//	for (auto& rb : engineRb)
//	{
//		pointsAverage += rb->getPosition();
//		kdPointList_.emplace_back(rb->getPosition());
//	}
//
//	pointsAverage / (engineRb.size() + 1);
//
//	std::sort(kdPointList_.begin(), kdPointList_.end(), [pointsAverage](Vector2D a, Vector2D b)
//		{ return a < pointsAverage; }
//	);
//}
//
//bool KdTree::FirstDivisionIsX(Vector2D pointsAverage)
//{
//	if (pointsAverage.X() > pointsAverage.Y())
//		return true;
//	return false;
//}
//
//std::pair<int, float> KdTree::CreateConditions(Vector2D vec)
//{
//	if (DivisionIsX(currentLayer_))
//		return { currentLayer_, vec.X() };
//	return { currentLayer_, vec.Y() };
//}
//
//bool KdTree::DivisionIsX(const int x)
//{
//	if (x % 2 == 0)
//		return true;
//	return false;
//}
//
//bool KdTree::NumberGreater(const float numberCompared, const float comparator)
//{
//	if (numberCompared >= comparator)
//		return true;
//	return false;
//}
//
//void KdTree::GenerateRootNode()
//{
//	//float divider = 0;
//	//if (FirstDivisionIsX())
//	//	divider = kdBodyListX_.at(kdBodyListX_.size() / 2)->getPosition().X();
//	//else
//	//{
//	//	float divider = 1;
//	//	divider = kdBodyListY_.at(kdBodyListY_.size() / 2)->getPosition().Y();
//	//}
//	//nodeQueue_.push(KdNode(std::pair<int, float>(0, divider)));
//	//currentLayer_++;
//	//nodeQueue_.push(KdNode(CreateConditions(kdPointList_.at(0))));
//	nodeQueue_.push(KdNode(CreateConditions(kdPointList_.at(0))));
//	nodeQueue_.push(KdNode(&nodeQueue_.front()));
//	nodeQueue_.push(KdNode(&nodeQueue_.front()));
//	//nodeStack_.emplace(nodeQueue_.front());
//	nodeQueue_.pop();
//	for ( auto point : kdPointList_)
//	{
//		if (DivisionIsX(currentLayer_) && NumberGreater(nodeStack_.top().getDivider().second, point.X()))
//		{
//			nodeQueue_.front().addPointToList(point);
//		}
//	}
//	if (currentLayer_ < layerMax_ && nodeQueue_.front().getNumberOfPoints() > 2)
//	{
//		nodeQueue_.push(KdNode(&nodeQueue_.front()));
//		nodeQueue_.push(KdNode(&nodeQueue_.front()));
//	}
//	nodeQueue_.pop();
//
//	for ( auto point : kdPointList_)
//	{
//		if (DivisionIsX(currentLayer_) && !NumberGreater(nodeStack_.top().getDivider().second, point.X()))
//		{
//			nodeQueue_.front().addPointToList(point);
//		}
//	}
//	if (currentLayer_ < layerMax_ && nodeQueue_.front().getNumberOfPoints() > 2)
//	{
//		nodeQueue_.push(KdNode(&nodeQueue_.front()));
//		nodeQueue_.push(KdNode(&nodeQueue_.front()));
//	}
//	nodeQueue_.pop();
//}
//
//void KdTree::GenerateNode()
//{
//	/*if (nodeList_.at(nodeList_.size())->getLayer() == currentLayer_ &&
//		nodeList_.at(nodeList_.size() - 1)->getLayer() == currentLayer_)
//	{
//		currentLayer_++;
//		return;
//	}*/
//	if (DivisionIsX(currentLayer_))
//		nodeQueue_.front().setLayerAndDivider(std::pair(currentLayer_, nodeStack_.top().getPointList().at(0).X()));
//	else
//		nodeQueue_.front().setLayerAndDivider(std::pair(currentLayer_, nodeStack_.top().getPointList().at(0).Y()));
//	for (auto point : nodeStack_.top().getPointList())
//	{
//		if (DivisionIsX(currentLayer_) && !NumberGreater(nodeStack_.top().getDivider().second, point.X()))
//		{
//			nodeQueue_.front().addPointToList(point);
//		}
//	}
//
//}
//
//void KdTree::SortBodies()
//{
//
//}
