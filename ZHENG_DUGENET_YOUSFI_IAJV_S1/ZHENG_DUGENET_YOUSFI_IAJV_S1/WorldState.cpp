#include "WorldState.h"

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
	conditions->push_back(new pair<EffectCondition, int>(EC_POW, 0));
	effects->push_back(new pair<EffectCondition, int>(EC_WIN, 1));
	ActionsList->push_back(new Action("Attack", effects, conditions, 1));
	conditions->clear();
	effects->clear();
}