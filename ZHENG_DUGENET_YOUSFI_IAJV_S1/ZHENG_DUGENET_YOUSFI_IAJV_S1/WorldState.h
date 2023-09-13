#pragma once
#include <cassert>
#include <list>
#include <utility>

#include "Action.h"

using namespace std;

class WorldState
{
public:
	unsigned int Wood;
	unsigned int Food;
	unsigned int Inf;
	unsigned int Cav;
	unsigned int Ran;
	unsigned int Power;
	unsigned int FreeVillager;
	unsigned int FoodVillager;
	unsigned int WoodVillager;
	unsigned int PlaceTotal;
	unsigned int PlaceLeft;
	unsigned int EnnemyInf;
	unsigned int EnnemyCav;
	unsigned int EnnemyRan;
	unsigned int EnemyPower;
	list<Action*>* ActionsList; //à retirer du ws pour les perfs
	Action* firstAction;

	WorldState() : Wood(0), Food(0), Inf(0), Cav(0), Ran(0), Power(0),
		FreeVillager(0), FoodVillager(0), WoodVillager(0), PlaceTotal(0), PlaceLeft(0), EnnemyInf(0), EnnemyCav(0),
		EnnemyRan(0), EnemyPower(0), ActionsList(new list<Action*>), firstAction(nullptr){}

	// Constructeur par copie
	WorldState(const WorldState* other)
		: Wood(other->Wood), Food(other->Food), Inf(other->Inf), Cav(other->Cav),
		Ran(other->Ran), Power(other->Power), FreeVillager(other->FreeVillager),
		WoodVillager(other->Wood), FoodVillager(other->FoodVillager),
		PlaceTotal(other->PlaceTotal), PlaceLeft(other->PlaceLeft),
		EnnemyInf(other->EnnemyInf), EnnemyCav(other->EnnemyCav),
		EnnemyRan(other->EnnemyRan), EnemyPower(other->EnemyPower), firstAction(other->firstAction)
	{
		if (other->ActionsList)
		{
			ActionsList = new list<Action*>(*(other->ActionsList));
		}
		else
		{
			ActionsList = new list<Action*>();
		}
	}

	// destructeur
	~WorldState()
	{
		//delete ActionsList;
	}

	void init();
	void Execution(const Action* action, bool print);
	const unsigned int CheckActionCondition(const Action action);
	const unsigned int CheckActionEffect(const Action action);
	const bool CheckCondition(const pair<EffectCondition, unsigned int>* condition);
};
