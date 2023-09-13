#include "Action.h"

const list<pair<EffectCondition, int>*>* Action::getConditions() const
{
	return Conditions;
}

const list<pair<EffectCondition, int>*>* Action::getEffects() const
{
	return Effects;
}
