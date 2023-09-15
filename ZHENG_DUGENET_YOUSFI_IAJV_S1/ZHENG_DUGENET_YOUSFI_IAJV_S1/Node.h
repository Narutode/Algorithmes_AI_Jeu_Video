#pragma once
#include <vector>
#include "WorldState.h"
using namespace std;
class Action;
class Node
{
	public:
		Action action;
		vector<Action> prevActions;
		vector<EffectCondition> preCondition;
		//unsigned int cost;
		//unsigned int unfulfilledCount;
		//WorldState worldstate;

		Node(const Action act, vector<Action> pAct, vector<EffectCondition> preC) : action(act), prevActions(pAct), preCondition(preC)
		{	};
		~Node()
		{
		}
		Node& operator=(const Node& other)
		{
			// V�rifiez si c'est la m�me instance
			if (this == &other)
			{
				return *this; // �vitez une auto-attribution
			}

			// Copiez les membres de l'autre instance
			action = other.action;
			prevActions = other.prevActions;
			preCondition = other.preCondition;

			return *this;
		}
};