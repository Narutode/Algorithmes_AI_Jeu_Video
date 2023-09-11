#include "Action.h"

list<EffectCondition>* Action::getCconditions()
{
	list<EffectCondition>* listCond = new list<EffectCondition>();
	for (const pair<EffectCondition, int>* condition : *Conditions) {
		listCond->push_back(condition->first);
	}
	return ;
}

list<EffectCondition>* Action::getEffects()
{
	list<EffectCondition>* listEff = new list<EffectCondition>();
	for (const pair<EffectCondition, int>* effect : *Effects) {
		listEff->push_back(effect->first);
	}
	return;
}
