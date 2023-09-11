
#include <cassert>
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
	unsigned int Wood;
	unsigned int Food;
	unsigned int Inf;
	unsigned int Cav;
	unsigned int Ran;
	unsigned int Villager;
	unsigned int PlaceTotal;
	unsigned int PlaceActually;
	unsigned int EnnemyInf;
	unsigned int EnnemyCav;
	unsigned int EnnemyRan;
	void init() {
		Villager += MainVariable::StartNbVillager;
		PlaceTotal += MainVariable::StartNbPlace;
		assert(PlaceTotal<Villager);
		PlaceActually += MainVariable::StartNbPlace - MainVariable::StartNbVillager;
		EnnemyInf += MainVariable::StartEnnemiInf;
		EnnemyCav += MainVariable::StartEnnemiCav;
		EnnemyRan += MainVariable::StartEnnemiRan;
		Wood += MainVariable::StartNbWood;
		Food += MainVariable::StartNbFood;

	};
};



