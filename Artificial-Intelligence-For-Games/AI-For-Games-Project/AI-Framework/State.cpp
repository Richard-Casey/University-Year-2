#include "BaseEntity.h"
#include "State.h"
#include "Prey.h"
#include "Hunter.h"

#include "UtilRandom.h"

#define _USE_MATH_DEFINES
#include <math.h>

void RestState::Enter(Prey* owner)
{
	owner->ZeroVelocity();
}

State* RestState::Execute(Prey* owner)
{
	owner->gainStamina();

	sf::Vector2f tmp = owner->getPosition() - owner->getHunter()->getPosition();

	//normalise - pmt = position minus target
	float length = sqrt((tmp.x * tmp.x) + (tmp.y * tmp.y));

	if (length <= safeZone)
	{
		std::cout << "Enter RunAway from Rest\n";
		return new RunAwaystate();
	}

	if (owner->getStamina() >= MaxStamina)
	{
		std::cout << "Enter Wonder from Rest\n";
		return new WonderState();
	}

	return nullptr;
}

State* RunAwaystate::Execute(Prey* owner)
{
	sf::Vector2f tmp = owner->getPosition() - owner->getHunter()->getPosition();

	//normalise - pmt = position minus target
	float length = sqrt((tmp.x * tmp.x) + (tmp.y * tmp.y));

	owner->drainStamina();

	if (length <= 0.1f)
	{
		tmp = sf::Vector2f(UtilRandom::instance()->GetRange(-1.0f, 1.0f), UtilRandom::instance()->GetRange(-1.0f, 1.0f));
	}
	//{ length = 0.1f; };
	tmp.x = tmp.x / length;
	tmp.y = tmp.y / length;

	// atan2(y,x)
	auto velocity = owner->getVelocity();
	float mag = sqrt(velocity.x * velocity.x + velocity.y * velocity.y);
	float angle = atan2(velocity.y, velocity.x) * (180.0f / M_PI);
	owner->setRotation(angle);

	sf::Vector2f desiredVelocity = tmp;
	owner->applyForce(tmp - owner->getVelocity());

	if (length > safeZone + 25) // If hunter is over 200.0f away then enter the rest state
	{
		printf("Entered Wonder from RunAway\n");
		return new WonderState();
	}

	if (length <= catchZone)
	{
		std::cout << "EnterCaught from RunAway\n";
		return new CaughtState();
	}

	if (owner->getHealth() <= 0)
	{
		printf("Enter Die State from Runaway State");
		return new DieState;
	}

	return nullptr;
}

State* WonderState::Execute(Prey* owner)
{
	owner->drainStamina();
	sf::Vector2f tmp = owner->getPosition() - owner->getHunter()->getPosition();
	float length = sqrt((tmp.x * tmp.x) + (tmp.y * tmp.y));

	if (owner->getStamina() <= 0.0f)
	{
		printf("Resting from Wonder\n");
		return new RestState();
	}

	if (length <= safeZone)
	{
		printf("Running Away from Wonder\n");
		return new RunAwaystate();
	}

	// change current angle slightly
	float angle = owner->getRotation();
	const float angleModifier = 1.5f;
	float newangle = UtilRandom::instance()->GetRange(angle - angleModifier, angle + angleModifier);

	owner->setRotation(newangle);

	sf::Vector2f velocity = sf::Vector2f((float)cos(newangle * M_PI / 180), (float)sin(newangle * M_PI / 180));

	sf::Vector2f force = velocity - owner->getVelocity();
	owner->applyForce(force);

	return nullptr;
}

State* DieState::Execute(Prey* owner)
{
	if (owner->getHealth() <= 0)
	{
		owner->ZeroVelocity();
		owner->setRotation(0);
		owner->dieTimer++;
		if (owner->dieTimer >= 200)
		{
			owner->resetHealth();
			owner->dieTimer = 0;
			owner->RandomisePosition();
			return new WonderState;
		}

		return new DieState;
	}
}

State* losingHealthState::Execute(Prey* owner)
{
	owner->loseHealth();
	owner->ZeroVelocity();
	return nullptr;
}

void RestState::Enter(Hunter* owner)
{
}

State* RestState::Execute(Hunter* owner)
{
	sf::Vector2f tmp = owner->getPosition() - owner->getPrey()->getPosition();

	//normalise - pmt = position minus target
	float length = sqrt((tmp.x * tmp.x) + (tmp.y * tmp.y));

	if (length >= safeZone)
	{
		//return new SeekState();
	}

	return nullptr;
}

State* SeekState::Execute(Hunter* owner)
{
	sf::Vector2f tmp = owner->getPosition() - owner->getPrey()->getPosition();

	sf::Vector2f desiredVelocity = tmp * MaxHunterSpeed;
	owner->applyForce(desiredVelocity - owner->getVelocity());

	//normalise - pmt = position minus target
	float length = sqrt((tmp.x * tmp.x) + (tmp.y * tmp.y));
	tmp.x = tmp.x / length;
	tmp.y = tmp.y / length;

	if (length > safeZone)

	{
		desiredVelocity = tmp * MaxHunterSpeed;
		owner->steering = desiredVelocity - owner->getVelocity();
		owner->applyForce(owner->steering);
	}

	return nullptr;
}

void CaughtState::Enter(Prey* owner)
{
	owner->ZeroVelocity();
	owner->setRotation(0);
}

State* CaughtState::Execute(Prey* owner)
{
	if (owner->getHealth() <= 0)
	{
		return new DieState();
	}

	return nullptr;
}

void CaughtState::Exit(Prey* owner)
{
	owner->RandomisePosition();
}