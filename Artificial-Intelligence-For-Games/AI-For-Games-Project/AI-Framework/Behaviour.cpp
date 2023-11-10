#include "Behaviour.h"
#include "Hunter.h"
#include <SFML/Graphics.hpp>
#include "UtilRandom.h"
#include "Prey.h"

// This function is called to update the MoveTo action for the Hunter
Status MoveToAction::update(Hunter* owner)
{
	printf("Moving To Action - Hunter\n");

	owner->drainStamina();

	// Get the distance between the hunter and the prey
	auto preyPos = owner->getPrey()->getPosition();
	auto hunterPos = owner->getPosition();
	auto direction = preyPos - hunterPos;
	auto length = std::max(0.1f, std::sqrt(direction.x * direction.x + direction.y * direction.y));

	// Normalize the direction vector
	direction /= length;

	// Set the desired velocity to move towards the prey
	auto desiredVelocity = direction;

	// Check if the hunter has passed the prey and adjust the desired velocity accordingly
	auto preyVelocity = owner->getPrey()->getVelocity();
	auto relativeSpeed = std::max(0.0f, owner->getVelocity().x * preyVelocity.x + owner->getVelocity().y * preyVelocity.y);
	if (relativeSpeed < 0.0f) {
		desiredVelocity = -preyVelocity;
	}

	// Apply the force to move towards the prey
	owner->applyForce(desiredVelocity - owner->getVelocity());

	// If the hunter is close enough to the prey, return Success
	if (length <= 10)
	{
		return Status::Success;
	}

	// If the hunter is too far from the prey, return Failure
	if (length >= safeZone + 50.0f)
	{
		return Status::Failure;
	}

	// Otherwise, return Running
	return Status::Running;
}

// This function is called to update the FindNearPreyQuery for the Hunter
Status FindNearPreyQuery::update(Hunter* owner) {
	Prey* prey = dynamic_cast<Prey*>(owner->getPrey());

	owner->drainStamina();

	// Get the distance between the hunter and the prey
	auto preyPos = owner->prey->getPosition();
	auto hunterPos = owner->getPosition();
	auto direction = preyPos - hunterPos;
	auto length = std::max(0.1f, std::sqrt(direction.x * direction.x + direction.y * direction.y));

	// Check if the prey is dead
	if (prey->isDead())
	{
		return Status::Running;
	}

	// If the hunter is close enough to the prey, return Success
	if (length <= safeZone + 50.0f)
	{
		std::cout << "FindNearPreyQuery Success\n";
		return Status::Success;
	}

	// Check if the hunter is already moving towards the prey
	if (owner->getCurrentAction() != "MoveTo")
	{
		owner->setCurrentAction("MoveTo");
		return Status::Running;
	}

	// If the hunter is not close enough and not already moving towards the prey, return Failure
	return Status::Failure;
}

// This function is called to update the KillPrey action for the Hunter
Status KillPrey::update(Hunter* owner)
{
	// Cast the prey object to the Prey class
	Prey* prey = dynamic_cast<Prey*>(owner->getPrey());

	// If the prey is not a Prey object, return Failure
	if (prey == nullptr)
	{
		return Status::Failure;
	}

	// Check if the prey is already dead
	if (prey->isDead())
	{
		return Status::Success;
	}

	// Reduce the health of the prey and set its velocity and the hunter's velocity to zero
	prey->loseHealth();
	prey->ZeroVelocity();
	owner->ZeroVelocity();

	// If the prey is dead, return Success
	if (prey->isDead())
	{
		return Status::Success;
	}

	// If the prey is alive, return Running
	if (!prey->isDead())
	{
		return Status::Running;
	}

	// Prey is neither alive nor dead (some error occurred), return Failure
	return Status::Failure;
}

Status HunterRoam::update(Hunter* owner)
{
	// reduce hunter's stamina
	owner->drainStamina();

	// if stamina is depleted, return failure status
	if (owner->getStamina() <= 0.0f)
		return Status::Failure;

	// if the hunter's stamina drops below a certain threshold, return to the resting behavior
	if (owner->getStamina() < 50.0f && owner->getCurrentAction() != "Rest")
	{
		owner->setCurrentAction("Rest");
		return Status::Running;
	}

	// calculate a new angle within a range based on current angle
	float angle = owner->getRotation();
	const float angleModifier = 1.5f;
	float newangle = UtilRandom::instance()->GetRange(angle - angleModifier, angle + angleModifier);

	// set the new angle and calculate a velocity vector based on it
	owner->setRotation(newangle);
	sf::Vector2f velocity = sf::Vector2f((float)cos(newangle * M_PI / 180), (float)sin(newangle * M_PI / 180));

	// calculate a force vector based on the difference between current velocity and desired velocity
	sf::Vector2f force = velocity - owner->getVelocity();
	owner->applyForce(force);

	// return success status
	return Status::Success;
}

Status HunterRest::update(Hunter* owner)
{
	// increase hunter's stamina and reset its rotation and velocity
	owner->gainStamina();
	owner->setRotation(0);
	owner->ZeroVelocity();

	// if the hunter's stamina has reached maximum, return success status
	if (owner->getStamina() >= MaxStamina)
	{
		return Status::Success;
	}

	// if the hunter's stamina is not at maximum, return running status
	return Status::Running;
}

Status HunterFindHome::update(Hunter* owner)
{
	// if the hunter already has a path, return success status
	if (!owner->path.empty()) return Status::Success;

	// get the grid positions of the hunter and its home
	auto hunterNode = owner->getGridPosition();
	auto homeNode = owner->getHomePosition();

	// calculate a path from the hunter's position to its home using A* pathfinding
	owner->path = owner->_grid->aStarPathfinding(hunterNode.x, hunterNode.y, homeNode.x, homeNode.y);

	// if no path was found, return failure status
	if (owner->path.empty()) return Status::Failure;

	// if a path was found, return success status
	return Status::Success;
}

Status HunterFollowPath::update(Hunter* owner)
{
	// If the Hunter object's path is empty, return Failure status
	if (owner->path.empty()) return Status::Failure;

	// Get the coordinates of the current target cell in the path
	auto currentTarget = owner->path.back();
	float cellX = (currentTarget->x * currentTarget->width) + (currentTarget->width / 2.0f);
	float cellY = (currentTarget->y * currentTarget->height) + (currentTarget->height / 2.0f);

	// Create a vector representing the center of the current target cell
	sf::Vector2f cellPosition(cellX, cellY);

	// Calculate the vector between the Hunter's current position and the center of the current target cell
	sf::Vector2f tmp = cellPosition - owner->getPosition();

	// Calculate the length of the vector
	float length = sqrt((tmp.x * tmp.x) + (tmp.y * tmp.y));

	// Ensure length is not zero to avoid dividing by zero
	if (length == 0) { length = 0.1f; };

	// Normalize the vector by dividing each component by the length
	tmp.x = tmp.x / length;
	tmp.y = tmp.y / length;

	// Calculate the desired velocity vector for the Hunter to move towards the current target cell
	sf::Vector2f desiredVelocity = tmp;

	// Apply a force to the Hunter to move it towards the current target cell
	owner->applyForce(tmp - owner->getVelocity());

	// If the distance to the current target cell is less than or equal to 10 pixels,
	// set the color of the current target cell to transparent, pop it from the path,
	// and check if the path is now empty. If it is, return Success status.
	if (length <= 10)
	{
		currentTarget->shape.setFillColor(sf::Color::Transparent);
		owner->path.pop_back();
		if (owner->path.empty())
			return Status::Success;
	}

	// Return Running status to indicate the update is still in progress
	return Status::Running;
}