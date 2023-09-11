#include "Action.h"

const list<pair<EffectCondition, int>*>* Action::getConditions()
{
	return Conditions;
}

const list<pair<EffectCondition, int>*>* Action::getEffects()
{
	return Effects;
}
