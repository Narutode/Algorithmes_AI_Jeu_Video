#pragma once
#include <map>
#include "WorldState.h"
#include "Node.h"

class GOAP
{
	public :
		WorldState* ws;
		map<EffectCondition, Action> mapAction;
		vector<Action> ActionsList;
		Action firstAction;

			const Node const findBestAction();
		const unsigned int getLowestUnfulfilledCount(const vector<Node> nodeList);
		GOAP(WorldState* curWS);
};