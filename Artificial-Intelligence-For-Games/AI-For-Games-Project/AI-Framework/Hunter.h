#pragma once
#include "BaseEntity.h"
#include "State.h"
#include "Behaviour.h"

#include "GridManager.h"

using namespace std;
using namespace sf;

class Hunter : public BaseEntity
{
public:
	Hunter();
	~Hunter();
	void Think(float dt);
	void Seek();

	BaseEntity* prey;
	BaseEntity* home;
	BaseEntity* getPrey() { return prey; }
	Hunter(BaseEntity* _prey);
	State* currentState;
	bool setPreyDead = false;

	sf::Vector2f target;
	sf::Vector2f maxSpeed;
	sf::Vector2f desiredVelocity;
	sf::Vector2f steering;

	float getStamina() { return stamina; }
	void drainStamina(float drain_amount = 15.0f) {
		float newVal = stamina - (drain_amount * deltaTime);
		stamina = max(0.0f, newVal);
	}
	void gainStamina(float gain_amount = 25.0f) { stamina = min(MaxStamina, stamina + gain_amount * deltaTime); }

	sf::Vector2f getGridPosition();
	sf::Vector2f getHomePosition();

	GridManager* _grid;

	std::vector<Node*> path;
	std::string getCurrentAction() const { return currentAction; }
	void setCurrentAction(const std::string& action) { currentAction = action; }

private:

	std::string currentAction;
	void buildBehaviourTree();
	float deltaTime;

	Selector* root;
	float stamina = 50.0f;
};

class HunterHome : public BaseEntity
{
public:
	HunterHome();
	~HunterHome();
	// Pointer to BaseEntity m_Home
	BaseEntity* m_Home;

	// Public member function for thinking
	void Think();
};