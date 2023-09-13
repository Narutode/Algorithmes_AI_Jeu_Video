#pragma once
#include "WorldState.h"
#include "Node.h"

class GOAP
{
	public :
		WorldState ws;
		GOAP(const WorldState curWS) : ws(curWS) {}
		const Node* const findBestAction();
		Node* findNodeWithLowestCost(const list<Node*>& nodeList);
		const unsigned int getLowestUnfulfilledCount(const list<Node*>& nodeList);
};