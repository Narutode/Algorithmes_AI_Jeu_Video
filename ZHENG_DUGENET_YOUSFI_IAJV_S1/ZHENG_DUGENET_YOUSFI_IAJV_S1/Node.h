#pragma once
#include "Action.h"
class Node
{
	public:
		const Action* action;
		const Node* prevNode;
		unsigned int cost;
		Node(const Action* const act, const Node* const pNode) : action(act), prevNode(pNode), cost(0) {};
		~Node()
		{
			delete prevNode;
		}
};