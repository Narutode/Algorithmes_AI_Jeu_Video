#include <iostream>
#include "WorldState.h"
using namespace std;

namespace MainVariable
{
	constexpr int StartNbVillager = 1;
	constexpr int StartNbPlace = 1;
	constexpr int StartEnnemiInf = 2;
	constexpr int StartEnnemiCav = 1;
	constexpr int StartEnnemiRan = 3;
	constexpr int StartNbWood = 0;
	constexpr int StartNbFood = 0;
}

void WorldState::init() {
	FreeVillager += MainVariable::StartNbVillager;
	PlaceTotal += MainVariable::StartNbPlace;
	assert(PlaceTotal >= FreeVillager);
	PlaceLeft += MainVariable::StartNbPlace - MainVariable::StartNbVillager;
	EnnemyInf += MainVariable::StartEnnemiInf;
	EnnemyCav += MainVariable::StartEnnemiCav;
	EnnemyRan += MainVariable::StartEnnemiRan;
	Wood += MainVariable::StartNbWood;
	Food += MainVariable::StartNbFood;
	EnemyPower = EnnemyInf + EnnemyCav + EnnemyRan;

	ActionsList = new list<Action*>();
	list<pair<EffectCondition, unsigned int>*> effects;
	list<pair<EffectCondition, unsigned int>*> conditions;

	//Action create infantry
	conditions.push_back(new pair<EffectCondition, unsigned int>(EC_FOOD, 10));
	conditions.push_back(new pair<EffectCondition, unsigned int>(EC_PLACE, 1));
	effects.push_back(new pair<EffectCondition, unsigned int>(EC_INF, 1));
	ActionsList->push_back(new Action("CreateInfantry", effects, conditions,3));
	conditions.clear();
	effects.clear();

	//Action create cavalry
	conditions.push_back(new pair<EffectCondition, unsigned int>(EC_FOOD, 30));
	conditions.push_back(new pair<EffectCondition, unsigned int>(EC_PLACE, 2));
	effects.push_back(new pair<EffectCondition, unsigned int>(EC_CAV, 1));
	ActionsList->push_back(new Action("CreateCavalry", effects, conditions, 4));
	conditions.clear();
	effects.clear();

	//Action create range
	conditions.push_back(new pair<EffectCondition, unsigned int>(EC_FOOD, 10));
	conditions.push_back(new pair<EffectCondition, unsigned int>(EC_PLACE, 1));
	effects.push_back(new pair<EffectCondition, unsigned int>(EC_RAN, 1));
	ActionsList->push_back(new Action("CreateRange", effects, conditions, 2));
	conditions.clear();
	effects.clear();

	//Action create villager
	conditions.push_back(new pair<EffectCondition, unsigned int>(EC_FOOD, 5));
	conditions.push_back(new pair<EffectCondition, unsigned int>(EC_PLACE, 1));
	effects.push_back(new pair<EffectCondition, unsigned int>(EC_VIL, 1));
	ActionsList->push_back(new Action("CreateVillager", effects, conditions, 1));
	conditions.clear();
	effects.clear();

	//Action create house
	conditions.push_back(new pair<EffectCondition, unsigned int>(EC_WOOD, 10));
	conditions.push_back(new pair<EffectCondition, unsigned int>(EC_VIL, 1));
	effects.push_back(new pair<EffectCondition, unsigned int>(EC_PLACE, 5));
	ActionsList->push_back(new Action("CreateHouse", effects, conditions, 3));
	conditions.clear();
	effects.clear();

	//Action get wood
	conditions.push_back(new pair<EffectCondition, unsigned int>(EC_VIL, 1));
	effects.push_back(new pair<EffectCondition, unsigned int>(EC_WOOD, 1));
	ActionsList->push_back(new Action("GetWood", effects, conditions, 2));
	conditions.clear();
	effects.clear();

	//Action get food
	conditions.push_back(new pair<EffectCondition, unsigned int>(EC_VIL, 1));
	effects.push_back(new pair<EffectCondition, unsigned int>(EC_FOOD, 1));
	ActionsList->push_back(new Action("GetFood", effects, conditions, 2));
	conditions.clear();
	effects.clear();

	//Action attack
	conditions.push_back(new pair<EffectCondition, unsigned int>(EC_INF, EnnemyCav));
	conditions.push_back(new pair<EffectCondition, unsigned int>(EC_RAN, EnnemyInf));
	conditions.push_back(new pair<EffectCondition, unsigned int>(EC_CAV, EnnemyRan));
	effects.push_back(new pair<EffectCondition, unsigned int>(EC_WIN, 1));
	ActionsList->push_back(new Action("Attack", effects, conditions, 1));
	firstAction = new Action("Attack", effects, conditions, 1);
	conditions.clear();
	effects.clear();
}
void WorldState::Execution(const Action* action, bool print)
{
	for (const pair<EffectCondition, unsigned int>* condition : *(action->getConditions()))
	{
		switch (condition->first) {
			case EC_FOOD:
				assert(Food >= condition->second);
				Food -= condition->second;
				break;
			case EC_WOOD:
				assert(Wood >= condition->second);
				Wood -= condition->second;
				break;
			case EC_PLACE:
				assert(PlaceLeft >= condition->second);
				PlaceLeft -= condition->second;
				break;
			case EC_VIL:
				if(FreeVillager > 0) {
					assert(FreeVillager >= condition->second);
					//FreeVillager -= condition->second;
				}
				break;
			case EC_POW:
				assert(Power > EnemyPower);
				break;
		}
	}
	bool win = false;
	for (const pair<EffectCondition, unsigned int>* effets : *(action->getEffects()))
	{
		switch (effets->first) {
		case EC_FOOD:
			FoodVillager += 1;
			Food += effets->second * FoodVillager;
			break;
		case EC_WOOD:
			WoodVillager += 1;
			Wood += effets->second * WoodVillager;
			break;
		case EC_PLACE:
			PlaceLeft += effets->second;
			PlaceTotal += effets->second;
			break;
		case EC_VIL:
			FreeVillager += effets->second;
			break;
		case EC_WIN:
			win = true;
			break;
		case EC_INF:
			Inf += effets->second;
			Power += 1;
			break;
		case EC_CAV:
			Cav += effets->second;
			Power += 1;
			break;
		case EC_RAN:
			Ran += effets->second;
			Power += 1;
			break;
		}
	}
	if (print) {
		cout << "Execute " << action->Name << endl;
		cout << "Nb food = " << Food << endl;
		cout << "Nb wood = " << Wood << endl;
		cout << "Nb Inf = " << Inf << endl;
		cout << "Nb Cav = " << Cav << endl;
		cout << "Nb Ran = " << Ran << endl;
		cout << "Power = " << Power << endl;
		cout << "Nb Free villager = " << FreeVillager << endl;
		cout << "Nb Food villager = " << FoodVillager << endl;
		cout << "Nb Wood villager = " << WoodVillager << endl;
		cout << "Place total = " << PlaceTotal << endl;
		cout << "Place left = " << PlaceLeft << endl;
		cout << "Ennemy Power = " << EnemyPower << endl << endl << endl;
		if(win)
			cout << "YOU WIIIIIIIINNNNNNNNNNNNNNNNNNNNN" << endl << endl << endl;
	}
}

const unsigned int WorldState::CheckActionCondition(const Action action)
{
	unsigned int Unfulfilledconditions = 0;
	for (const pair<EffectCondition, unsigned int>* condition : *(action.getConditions()))
	{
		switch (condition->first) {
			case EC_FOOD:
				if (Food < condition->second)
					Unfulfilledconditions += condition->second - Food;
				break;
			case EC_WOOD:
				if(Wood < condition->second)
					Unfulfilledconditions += condition->second - Wood;
				break;
			case EC_PLACE:
				if(PlaceLeft < condition->second)
					Unfulfilledconditions += condition->second - PlaceLeft;
				break;
			case EC_VIL:
				if(FreeVillager > 0)
					if(FreeVillager < condition->second)
						Unfulfilledconditions += condition->second - FreeVillager;
				break;
			case EC_POW:
				if(Power < EnemyPower)
					Unfulfilledconditions += EnemyPower - Power;
				break;
			case EC_INF:
				if (Inf < condition->second)
					Unfulfilledconditions += condition->second - Inf;
				break;
			case EC_RAN:
				if (Ran < condition->second)
					Unfulfilledconditions += condition->second - Ran;
				break;
			case EC_CAV:
				if (Cav < condition->second)
					Unfulfilledconditions += condition->second - Cav;
				break;
		}
	}
	return Unfulfilledconditions;
}

const bool WorldState::CheckCondition(const pair<EffectCondition, unsigned int>* condition)
{
	switch (condition->first) {
		case EC_FOOD:
			if (Food < condition->second)
				return false;
			break;
		case EC_WOOD:
			if (Wood < condition->second)
				return false;
			break;
		case EC_PLACE:
			if (PlaceLeft < condition->second)
				return false;
			break;
		case EC_VIL:
			if(FreeVillager > 0)
				if (FreeVillager < condition->second)
					return false;
			break;
		case EC_POW:
			if (Power <= EnemyPower)
				return false;
			break;
		case EC_INF:
			if (Inf < condition->second)
				return false;
			break;
		case EC_RAN:
			if (Ran < condition->second)
				return false;
			break;
		case EC_CAV:
			if (Cav < condition->second)
				return false;
			break;
	}
	return true;
}
