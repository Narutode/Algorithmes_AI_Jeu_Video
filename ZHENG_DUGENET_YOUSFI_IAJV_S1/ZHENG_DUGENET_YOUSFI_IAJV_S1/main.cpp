#include <iostream>
#include "WorldState.h"
#include "GOAP.h"
using namespace std;

int main(void)
{
	WorldState* ws = new WorldState();
	ws->init();
	while(true) {
		GOAP* goap = new GOAP(ws);
		const Node* bestNode = goap->findBestAction();
		ws->Execution(bestNode->action, true);
		if (bestNode->action->Name == "Attack")
			break;
	}

	return 0;
}