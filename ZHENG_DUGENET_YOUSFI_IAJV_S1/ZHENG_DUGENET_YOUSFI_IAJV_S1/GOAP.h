#pragma once
#include "WorldState.h"
class GOAP
{
	public :
		WorldState ws;
		GOAP(const WorldState& curWS) : ws(curWS) {}
		const Action* const findBestAction();
};

