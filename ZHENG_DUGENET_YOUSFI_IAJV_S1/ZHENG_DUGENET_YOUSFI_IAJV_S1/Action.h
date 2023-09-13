#pragma once

#include <string>
#include <list>
#include <utility>
using namespace std;

enum EffectCondition
{
	EC_WOOD,
	EC_FOOD,
	EC_PLACE,
	EC_INF,
	EC_CAV,
	EC_RAN,
	EC_VIL,
	EC_POW,
	EC_WIN
};

class Action
{
	private:
		const list<pair<EffectCondition, int>*>* Effects;
		const list<pair<EffectCondition, int>*>* Conditions;
	public:
		const string Name;
		const int Cost;
		Action(const string name, const list<pair<EffectCondition, int>*>* effects, const list<pair<EffectCondition, int>*>* conditions, int const cost)
			: Name(name), Effects(effects), Conditions(conditions), Cost(cost) {};
		const list<pair<EffectCondition, int>*>* getConditions() const;
		const list<pair<EffectCondition, int>*>* getEffects() const;
};