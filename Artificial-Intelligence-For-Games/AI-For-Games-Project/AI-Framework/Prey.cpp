#include "Prey.h"
#include "Hunter.h"
#include <iostream>
#include "State.h"

using namespace std;

Prey::Prey(BaseEntity* _hunter)
{
	currentState = new RestState();
	hunter = _hunter;
	dieTimer = 0;
}

Prey::~Prey()
{
	// Moved behaviours into State.cpp for FSM
}

void Prey::Flee()
{
	// Moved behaviours into State.cpp for FSM
}

void Prey::Rest()
{
	// Moved behaviours into State.cpp for FSM
}

void Prey::Wonder()
{
	// Moved behaviours into State.cpp for FSM
}

void Prey::Seek()
{
	// Moved behaviours into State.cpp for FSM
}

void Prey::Think(float dt)
{
	deltaTime = dt;

	if (currentState == nullptr)
	{
		currentState = new RestState();
	}

	State* newState = currentState->Execute(this);

	if (newState != nullptr)
	{
		delete currentState;
		currentState = newState;
		currentState->Enter(this);
	}
}

void Prey::loseHealth()
{
	health--;
	std::cout << health << endl;
}