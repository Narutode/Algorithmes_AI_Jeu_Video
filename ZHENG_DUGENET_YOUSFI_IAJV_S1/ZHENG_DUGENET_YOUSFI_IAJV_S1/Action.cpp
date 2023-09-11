#include "Action.h"

list<EffectCondition>* Action::getCconditions()
{
	list<EffectCondition>* listCond = new list<EffectCondition>();
	for (const pair<EffectCondition, int>* condition : *Conditions) {
		listCond->push_back(condition->first);
	}
	return ;
}

list<pair<EffectCondition, int>*> Action::getEffects()
{
	return Effects;
}