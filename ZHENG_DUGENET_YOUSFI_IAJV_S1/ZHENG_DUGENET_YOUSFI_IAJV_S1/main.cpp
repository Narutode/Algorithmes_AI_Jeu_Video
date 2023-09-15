#include <iostream>
#include <chrono>

#include "WorldState.h"
#include "GOAP.h"
using namespace std;

int main(void)
{
	auto start = chrono::high_resolution_clock::now();

	WorldState* ws = new WorldState();
	ws->init();
	GOAP* goap = new GOAP(ws);
	const Node bestNode = goap->findBestAction();

	ws->Execution(bestNode.action, true);


	auto end = chrono::high_resolution_clock::now();

	chrono::duration<double> elapsed = end - start;

	cout << "Temps ecoule : " << elapsed.count() << " secondes" << endl;

	return 0;
}