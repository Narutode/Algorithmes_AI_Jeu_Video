#include <iostream>
#include "WorldState.h"
#include "GOAP.h"
using namespace std;

int main(void)
{
	WorldState* ws = new WorldState();
	ws->init();
	GOAP* goap = new GOAP(ws);
}