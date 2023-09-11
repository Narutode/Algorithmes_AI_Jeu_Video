#include <cassert>
#include <list>
#include <utility>

#include "Action.h"
using namespace std;

namespace MainVariable
{
	constexpr int StartNbVillager = 1;
	constexpr int StartNbPlace = 1;
	constexpr int StartEnnemiInf = 2;
	constexpr int StartEnnemiCav = 2;
	constexpr int StartEnnemiRan = 2;
	constexpr int StartNbWood = 0;
	constexpr int StartNbFood = 0;
}
class WorldState
{
public:
	unsigned int Wood;
	unsigned int Food;
	unsigned int Inf;
	unsigned int Cav;
	unsigned int Ran;
	unsigned int Power;
	unsigned int Villager;
	unsigned int PlaceTotal;
	unsigned int PlaceLeft;
	unsigned int EnnemyInf;
	unsigned int EnnemyCav;
	unsigned int EnnemyRan;
	unsigned int EnemmyPower;
	list<Action*>* ActionsList;

	void init();
};



