#include "BaseEntity.h"
#include "UtilRandom.h"

#include <cstdlib> // for rand() and srand()
#include <ctime>   // for time()

using namespace sf;

std::vector<BaseEntity*> BaseEntity::Renderables;

BaseEntity::BaseEntity()
{
	// with no further information, we make some assumptions and set default values.
	filename = "assets\\boid.png";
	colourTint = sf::Color::Cyan;
}

BaseEntity::BaseEntity(std::string file) : filename(file)
{
	// with just a texture file, we default to a white tint (so no tint at all).
	colourTint = sf::Color::White;
}

BaseEntity::BaseEntity(std::string file, sf::Color colour) : filename(file), colourTint(colour)
{
}

BaseEntity::~BaseEntity()
{
}

void BaseEntity::Think(float dt)
{
	// set acceleration, somehow
}

void BaseEntity::Update(float dt)
{
	velocity += acceleration;

	// build a new position vector by adding a scaled version of the velocity vector
	sf::Vector2f pos = getPosition() + (velocity * movementSpeed);

	// ...

	const float maxTurningAngle = 180.0f; // maximum turning angle
	const float minTurningAngle = -180.0f; // minimum turning angle

	// Check if the object is out of the screen bounds
	if (pos.x > ScreenWidth)
	{
		// If the object is going right, it should turn left
		if (cos(getRotation() * M_PI / 180.0f) > 0.0f)
		{
			// Generate a random angle between minTurningAngle and maxTurningAngle
			float randomAngle = (float)(rand() % ((int)(maxTurningAngle - minTurningAngle) + 1)) + minTurningAngle;
			setRotation(getRotation() + randomAngle);
		}
		pos.x = ScreenWidth;
	}
	else if (pos.x < 0)
	{
		// If the object is going left, it should turn right
		if (cos(getRotation() * M_PI / 180.0f) < 0.0f)
		{
			// Generate a random angle between minTurningAngle and maxTurningAngle
			float randomAngle = (float)(rand() % ((int)(maxTurningAngle - minTurningAngle) + 1)) + minTurningAngle;
			setRotation(getRotation() + randomAngle);
		}
		pos.x = 0;
	}

	if (pos.y > ScreenHeight)
	{
		// If the object is going down, it should turn up
		if (sin(getRotation() * M_PI / 180.0f) > 0.0f)
		{
			// Generate a random angle between minTurningAngle and maxTurningAngle
			float randomAngle = (float)(rand() % ((int)(maxTurningAngle - minTurningAngle) + 1)) + minTurningAngle;
			setRotation(getRotation() + randomAngle);
		}
		pos.y = ScreenHeight;
	}
	else if (pos.y < 0)
	{
		// If the object is going up, it should turn down
		if (sin(getRotation() * M_PI / 180.0f) < 0.0f)
		{
			// Generate a random angle between minTurningAngle and maxTurningAngle
			float randomAngle = (float)(rand() % ((int)(maxTurningAngle - minTurningAngle) + 1)) + minTurningAngle;
			setRotation(getRotation() + randomAngle);
		}
		pos.y = 0;
	}

	// update our position
	setPosition(pos);

	acceleration *= 0.0f;
}

void BaseEntity::RandomisePosition()
{
	// set a random starting position.
	float startX = UtilRandom::instance()->GetRange(0, ScreenWidth);
	float startY = UtilRandom::instance()->GetRange(0, ScreenHeight);
	setPosition(startX, startY);
}

void BaseEntity::ResetVelocity()
{
	// select a random angle
	float angle = UtilRandom::instance()->GetRange(0, 361);
	// set our rotation value
	setRotation(angle);
	// and assign a velocity, we need to convert angle to radians so it plays nicely with cos and sin.
	velocity = sf::Vector2f((float)cos(angle * M_PI / 180), (float)sin(angle * M_PI / 180));
}

sf::Vector2f BaseEntity::getVelocity()
{
	return velocity;
}

void BaseEntity::applyForce(const sf::Vector2f& force)
{
	acceleration += force;

	// Add Drag force
	const float dragCoeff = 0.01f;
	sf::Vector2f dragforce = -velocity * dragCoeff;
	acceleration += dragforce;
}

void BaseEntity::Initialize()
{
	RandomisePosition();

	// load the texture into memory
	texture.loadFromFile(filename);
	texture.setSmooth(true);
	// and provide the sprite with a pointer to the texture object
	// if the texture object is destroyed (goes out of scope etc) then the sprite will display weirdly
	sprite.setTexture(texture);
	// set up our colour tint
	sprite.setColor(colourTint);

	sprite.setOrigin(texture.getSize().x / 2, texture.getSize().y / 2);

	ResetVelocity();

	// add the entity to the list of renderables.
	Renderables.push_back(this);
}