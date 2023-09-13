#include "Action.h"

const list<pair<EffectCondition, unsigned int>*>* Action::getConditions() const
{
	return Conditions;
}

const list<pair<EffectCondition, unsigned int>*>* Action::getEffects() const
{
	return Effects;
}
