#include "GOAP.h"
#include "Node.h"

const Action* const GOAP::findBestAction()
{
	//bool actionFound = false;
	list<Node*>* openNode = new list<Node*>();
	openNode->push_back(new Node(ws.firstAction, nullptr));
	list<EffectCondition>* listConditions = new list<EffectCondition>();
	for (EffectCondition cond : *ws.firstAction->getCconditions()) {
		listConditions->push_back(cond);
	}

	for (Node* node : *openNode) {

	}

	while (actionToCheck->size() > 0)
	{
		for (Action* actCheck : *actionToCheck) {
			if(ws.CheckCondition(actCheck))
			for (const Action* act : *(ws.ActionsList)) {
				for (const pair<EffectCondition, int>* condition : *(act->Conditions)) {

				}
			}
		}




	}
}