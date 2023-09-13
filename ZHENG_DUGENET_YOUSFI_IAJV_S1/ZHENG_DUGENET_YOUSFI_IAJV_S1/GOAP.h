#pragma once
#include "WorldState.h"
#include "Node.h"

class GOAP
{
	public :
		WorldState* ws;
		GOAP(WorldState* curWS)
		{
			ws = new WorldState(curWS);
		}
		const Node* const findBestAction();
		const unsigned int getLowestUnfulfilledCount(const vector<Node*> nodeList);
};