#pragma once

#include <string>
#include <list>
#include <utility>
#include <vector>

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
	vector<pair<EffectCondition, unsigned int>> Effects;
	vector<pair<EffectCondition, unsigned int>> Conditions;
public:
	string Name;
	Action() : Name(""), Effects(vector<pair<EffectCondition, unsigned int>>()), Conditions(vector<pair<EffectCondition, unsigned int>>()) {};
	Action(const string name, vector<pair<EffectCondition, unsigned int>> effects, const vector<pair<EffectCondition, unsigned int>> conditions, int const cost)
		: Name(name), Effects(effects), Conditions(conditions) {};
	Action(const Action* other) : Name(other->Name), Effects(other->Effects), Conditions(other->Conditions) {};
	const vector<pair<EffectCondition, unsigned int>> getConditions() const
	{
		return Conditions;
	}

	const vector<pair<EffectCondition, unsigned int>> getEffects() const
	{
		return Effects;
	}

	Action& operator=(const Action& other)
	{
		// Vérifiez si c'est la même instance
		if (this == &other)
		{
			return *this; // Évitez une auto-attribution
		}

		// Effectuez une copie en profondeur des membres
		Name = other.Name;
		Effects = other.Effects;
		Conditions = other.Conditions;

		return *this;
	}
};