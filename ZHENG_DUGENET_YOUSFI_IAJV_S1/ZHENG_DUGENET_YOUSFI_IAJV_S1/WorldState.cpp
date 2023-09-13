#include <iostream>
#include "WorldState.h"
using namespace std;

namespace MainVariable
{
	constexpr int StartNbVillager = 1;
	constexpr int StartNbPlace = 1;
	constexpr int StartEnnemiInf = 1;
	constexpr int StartEnnemiCav = 0;
	constexpr int StartEnnemiRan = 0;
	constexpr int StartNbWood = 0;
	constexpr int StartNbFood = 0;
}

void WorldState::init() {
	Villager += MainVariable::StartNbVillager;
	PlaceTotal += MainVariable::StartNbPlace;
	assert(PlaceTotal < Villager);
	PlaceLeft += MainVariable::StartNbPlace - MainVariable::StartNbVillager;
	EnnemyInf += MainVariable::StartEnnemiInf;
	EnnemyCav += MainVariable::StartEnnemiCav;
	EnnemyRan += MainVariable::StartEnnemiRan;
	Wood += MainVariable::StartNbWood;
	Food += MainVariable::StartNbFood;
	EnemyPower = EnnemyInf + EnnemyCav + EnnemyRan;

	ActionsList = new list<Action*>();
	list<pair<EffectCondition, int>*>* effects = new list<pair<EffectCondition, int>*>();
	list<pair<EffectCondition, int>*>* conditions = new list<pair<EffectCondition, int>*>();

	//Action create infantry
	conditions->push_back(new pair<EffectCondition, int>(EC_FOOD, 10));
	conditions->push_back(new pair<EffectCondition, int>(EC_PLACE, 1));
	effects->push_back(new pair<EffectCondition, int>(EC_INF, 1));
	ActionsList->push_back(new Action("CreateInfantry", effects, conditions,3));
	conditions->clear();
	effects->clear();

	//Action create cavalry
	conditions->push_back(new pair<EffectCondition, int>(EC_FOOD, 30));
	conditions->push_back(new pair<EffectCondition, int>(EC_PLACE, 2));
	effects->push_back(new pair<EffectCondition, int>(EC_CAV, 1));
	ActionsList->push_back(new Action("CreateCavalry", effects, conditions, 4));
	conditions->clear();
	effects->clear();

	//Action create range
	conditions->push_back(new pair<EffectCondition, int>(EC_FOOD, 10));
	conditions->push_back(new pair<EffectCondition, int>(EC_PLACE, 1));
	effects->push_back(new pair<EffectCondition, int>(EC_RAN, 1));
	ActionsList->push_back(new Action("CreateRange", effects, conditions, 2));
	conditions->clear();
	effects->clear();

	//Action create villager
	conditions->push_back(new pair<EffectCondition, int>(EC_FOOD, 5));
	conditions->push_back(new pair<EffectCondition, int>(EC_PLACE, 1));
	effects->push_back(new pair<EffectCondition, int>(EC_VIL, 1));
	ActionsList->push_back(new Action("CreateVillager", effects, conditions, 1));
	conditions->clear();
	effects->clear();

	//Action create house
	conditions->push_back(new pair<EffectCondition, int>(EC_WOOD, 10));
	conditions->push_back(new pair<EffectCondition, int>(EC_VIL, 1));
	effects->push_back(new pair<EffectCondition, int>(EC_PLACE, 5));
	ActionsList->push_back(new Action("CreateHouse", effects, conditions, 3));
	conditions->clear();
	effects->clear();

	//Action get wood
	conditions->push_back(new pair<EffectCondition, int>(EC_VIL, 1));
	effects->push_back(new pair<EffectCondition, int>(EC_WOOD, 1));
	ActionsList->push_back(new Action("GetWood", effects, conditions, 2));
	conditions->clear();
	effects->clear();

	//Action get food
	conditions->push_back(new pair<EffectCondition, int>(EC_VIL, 1));
	effects->push_back(new pair<EffectCondition, int>(EC_FOOD, 1));
	ActionsList->push_back(new Action("GetFood", effects, conditions, 2));
	conditions->clear();
	effects->clear();

	//Action attack
	conditions->push_back(new pair<EffectCondition, int>(EC_INF, EnnemyInf));
	conditions->push_back(new pair<EffectCondition, int>(EC_RAN, EnnemyRan));
	conditions->push_back(new pair<EffectCondition, int>(EC_CAV, EnnemyCav));
	effects->push_back(new pair<EffectCondition, int>(EC_WIN, 1));
	ActionsList->push_back(new Action("Attack", effects, conditions, 1));
	firstAction = new Action("Attack", effects, conditions, 1);
	conditions->clear();
	effects->clear();
}
void WorldState::Execution(const Action* action)
{
	bool conditionsSatisfied = true;
	cout << action->Name << endl;
	cout << "Nb food = " << Food << endl;
	cout << "Nb wood = " << Wood << endl;
	cout << "Nb Inf = " << Inf << endl;
	cout << "Nb Cav = " << Cav << endl;
	cout << "Nb Ran = " << Ran << endl;
	cout << "Power = " << Power << endl;
	cout << "Nb villager" << Villager << endl;
	cout << "Place total = " << PlaceTotal << endl;
	cout << "Place left = " << PlaceLeft << endl;
	cout << "Nb food = " << Food << endl;
	cout << "Ennemy Power = " << EnemyPower << endl;
	for (const pair<EffectCondition, int>* condition : *(action->getConditions()))
	{
		switch (condition->first) {
			case EC_FOOD:
				assert(Food < condition->second);
				Food -= condition->second;
				break;
			case EC_WOOD:
				assert(Wood < condition->second);
				Wood -= condition->second;
				break;
			case EC_PLACE:
				assert(PlaceLeft < condition->second);
				PlaceLeft -= condition->second;
				break;
			case EC_VIL:
				assert(Villager < condition->second);
				Villager -= condition->second;
				break;
			case EC_POW:
				assert(EnemyPower > Power);
				break;
		}
	}

	for (const pair<EffectCondition, int>* effets : *(action->getEffects()))
	{
		switch (effets->first) {
		case EC_FOOD:
			Food += effets->second;
			Villager -= 1;
			break;
		case EC_WOOD:
			Wood += effets->second;
			Villager -= 1;
			break;
		case EC_PLACE:
			PlaceLeft += effets->second;
			break;
		case EC_VIL:
			Villager += effets->second;
			break;
		case EC_WIN:
			cout << "YOU WINNNNNNNNNNNNNNNNNNNNNNNNNNNNNN" << endl;
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
}

const unsigned int WorldState::CheckAction(const Action action)
{
	unsigned int Unfulfilledconditions = 0;
	for (const pair<EffectCondition, int>* condition : *(action.getConditions()))
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
			if(Villager < condition->second)
				Unfulfilledconditions += condition->second - Villager;
			break;
		case EC_POW:
			if(Power < EnemyPower)
				Unfulfilledconditions += EnemyPower - Power;
			break;

		}
	}
	return true;
}

const bool WorldState::CheckCondition(const pair<EffectCondition, int>* condition)
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
		if (Villager < condition->second)
			return false;
		break;
	case EC_POW:
		if (Power < EnemyPower)
			return false;
		break;
	}
	return true;
}
