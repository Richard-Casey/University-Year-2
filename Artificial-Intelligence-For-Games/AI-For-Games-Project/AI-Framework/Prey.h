#pragma once
#include "BaseEntity.h"
#include "State.h"

using namespace std;
using namespace sf;

class Prey : public BaseEntity
{
public:
	Prey(BaseEntity* _hunter);
	Prey(Prey* _prey);
	~Prey();
	void Rest();
	void Flee();
	//void Die();
	void Wonder();
	void Seek();
	void Think(float dt);
	void loseHealth();

	float getStamina() { return stamina; }
	void drainStamina(float drain_amount = 15.0f)
	{
		stamina = max(0.0f, stamina - drain_amount * deltaTime);
	}

	void gainStamina(float gain_amount = 25.0f)
	{
		stamina = min(MaxStamina, stamina + gain_amount * deltaTime);
	}

	bool isDead() { return health <= 0.0f; }

	BaseEntity* getHunter() { return hunter; }

	float getHealth() { return health; }

	void resetHealth() { health = 50.0f; }

	Vector2f tmp;

	sf::Vector2f target;
	sf::Vector2f maxSpeed;
	sf::Vector2f desiredVelocity;
	sf::Vector2f steering;

	float deltaTime;
	float dieTimer;

private:
	float stamina = 100.0f;
	State* currentState;
	float health = 50.0f;

	BaseEntity* hunter;
	BaseEntity* prey;
};
