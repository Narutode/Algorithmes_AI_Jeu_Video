#pragma once
#include "WorldState.h"
class GOAP
{
	private :
		WorldState ws;
	public :
		GOAP(const WorldState& curWS) : ws(curWS) {}
		const Action* const findBestAction();
};

