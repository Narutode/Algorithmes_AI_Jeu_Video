#pragma once

#include <string>
#include <list>
#include <utility>
using namespace std;

enum EffectCondition
{
	WOOD,
	FOOD,
	PLACE,
	INF,
	CAV,
	RAN
};

class Action
{
	private:
		const string Name;
		const list<pair<EffectCondition, unsigned int>> Effects;
		const list<pair<EffectCondition, unsigned int>> Conditions;
	public:
		Action(const string name, const list<pair<EffectCondition, unsigned int>> effects, const list<pair<EffectCondition, unsigned int>> conditions)
			: Name(name), Effects(effects), Conditions(conditions){}
};