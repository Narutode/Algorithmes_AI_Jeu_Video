#pragma once
#include <vector>
#include "WorldState.h"
using namespace std;
class Action;
class Node
{
	public:
		Action* action;
		vector<Action*> prevNode;
		list<EffectCondition> preCondition;
		//unsigned int cost;
		//unsigned int unfulfilledCount;
		WorldState worldstate;

		Node(Action* const act, vector<Action*> pNode, WorldState ws, list<EffectCondition> preC) : action(act), prevNode(pNode), worldstate(ws), preCondition(preC)
		{	};
		~Node()
		{
		}
};