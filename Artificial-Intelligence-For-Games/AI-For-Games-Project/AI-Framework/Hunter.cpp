#include "Prey.h"
#include "Hunter.h"
#include <iostream>
#include "State.h"

// Constructor for the Hunter class
Hunter::Hunter()
{
	// Set the filename and colour tint for the sprite
	filename = "assets\\circle.png";
	colourTint = sf::Color::Red;

	// Set the movement speed
	movementSpeed = 7.5f;

	// Build the behaviour tree
	buildBehaviourTree();
}

// Constructor for the Hunter class with a prey parameter
Hunter::Hunter(BaseEntity* _prey)
{
	// Set the movement speed
	movementSpeed = 7.5f;

	// Build the behaviour tree
	buildBehaviourTree();
}

sf::Vector2f Hunter::getGridPosition()
{
	return _grid->getGridPosition(getPosition().x, getPosition().y);
}

sf::Vector2f Hunter::getHomePosition()
{
	return _grid->getGridPosition(home->getPosition().x, home->getPosition().y);
}

// Function to build the behaviour tree for the Hunter class
void Hunter::buildBehaviourTree()
{
	// Create the root node of the behaviour tree
	root = new Selector();

	// Create the Roam and HuntPrey selectors
	Selector* Roam = new Selector();
	Sequence* HuntPrey = new Sequence();
	Sequence* Rest = new Sequence();

	// Create the HunterRoam and HunterRest actions
	HunterRoam* hunterRoam = new HunterRoam();

	HunterFindHome* findHome = new HunterFindHome();
	HunterFollowPath* follow = new HunterFollowPath();
	HunterRest* hunterRest = new HunterRest();

	Rest->addChild(findHome);
	Rest->addChild(follow);
	Rest->addChild(hunterRest);

	// Create the FindNearPreyQuery, MoveToAction, and KillPrey actions
	FindNearPreyQuery* findPrey = new FindNearPreyQuery();
	MoveToAction* moveToTarget = new MoveToAction();
	KillPrey* killTarget = new KillPrey();

	// Add the HuntPrey and Roam selectors to the root node
	root->addChild(HuntPrey);
	root->addChild(Roam);

	// Add the HunterRoam and HunterRest actions to the Roam selector
	Roam->addChild(hunterRoam);
	Roam->addChild(Rest);

	// Add the FindNearPreyQuery, MoveToAction, and KillPrey actions to the HuntPrey sequence
	HuntPrey->addChild(findPrey);
	HuntPrey->addChild(moveToTarget);
	HuntPrey->addChild(killTarget);
}

// Destructor for the Hunter class
Hunter::~Hunter() {}

// Think method for Hunter class, which runs the behaviour tree
void Hunter::Think(float dt)
{
	sf::Vector2f currentPos = getPosition();

	//Calculate new position and velocity
	sf::Vector2f newPos = currentPos + velocity * dt + 0.5f * acceleration * dt * dt;
	sf::Vector2f newVel = velocity + acceleration * dt;

	// Interpolate position
	const float alpha = 0.01f;
	currentPos = alpha * newPos + (1.0f - alpha) * currentPos;

	// Update velocity and acceleration
	velocity = newVel;
	acceleration = sf::Vector2f(0, 0);

	// Set the delta time and tick the root node of the behaviour tree
	deltaTime = dt;
	root->Tick(this);
}

// Constructor for the HunterHome class
HunterHome::HunterHome()
{
	// Set the filename and colour tint for the sprite
	filename = "assets\\hunterhome.png";
	//filename = "C:\\Users\\Administrator\\OneDrive - University of Suffolk\\Desktop\\s233122\\implementation-Richard-Casey\\Build\\Assets\\hunterhome.png";
	colourTint = sf::Color::White;

	// Set the movement speed to 0
	movementSpeed = 0.0f;
}

// Destructor for the HunterHome class
HunterHome::~HunterHome() {}

// Think method for the HunterHome class, which sets the rotation to 0
void HunterHome::Think()
{
	this->setRotation(0);
}