#pragma once

#include <vector>

// Four possible outcomes for the Behaviour Tree
enum class Status
{
	Invalid,
	Running,
	Success,
	Failure
};

class Hunter;
class Prey;

class Behaviour
{
private:
	// The current status of the behaviour
	Status currentStatus;

protected:
	// These methods are intended to be overriden by child classes
	virtual void OnInit() {};
	virtual Status update(Hunter* owner) = 0;
	virtual void OnExit(Status) {};

public:
	Behaviour() : currentStatus(Status::Invalid) {};
	virtual ~Behaviour() {};

	// This method calls OnInit and update and returns the current status of the behaviour
	Status Tick(Hunter* owner)
	{
		if (currentStatus == Status::Invalid)
			OnInit();

		currentStatus = update(owner);

		// If status is not running return result - loop until complete (not running, either sucess or failure)
		if (currentStatus != Status::Running)
			OnExit(currentStatus);

		return currentStatus;
	};
};

// Composite nodes define the root of the branch and are the base rules for how the branch is executed
class Composite : public Behaviour
{
protected:
	// A vector containing pointers to the behaviour objects that are the children of this behaviour
	std::vector<Behaviour*> children;

public:
	void addChild(Behaviour* newChild)
	{
		children.push_back(newChild);
	}

	void removeChild(Behaviour* child)
	{
		children.erase(std::remove(children.begin(), children.end(), child), children.end());
	}

	void clearChildren()
	{
		children.clear();
	}
};

// A Sequence is the simplest CONTROLNODE, it executes its children one after the other and if they all succeed it returns success too
class Sequence : public Composite
{
private:
	std::vector<Behaviour*>::iterator currentChild;

protected:
	// Called when the sequence is first ticked
	virtual void OnInit() override
	{
		currentChild = children.begin();
	}

	// Called when the sequence finishes
	virtual void OnExit(Status status) override
	{
		currentChild = children.begin();
	}

	// Called every tick
	Status update(Hunter* owner) override
	{
		while (true)
		{
			Status s = (*currentChild)->Tick(owner);
			if (s != Status::Success)
				return s;
			if (++currentChild == children.end()) // Increment through children
				return Status::Success; // Reached the end of its children
		}
	}
};

// Also known as "FallBackNodes", selector nodes are nodes that can express a fallback strategy, such as what to do it a child returns FAILURE
class Selector : public Composite
{
private:
	std::vector<Behaviour*>::iterator currentChild;

protected:
	// Called when the selector is first ticked
	virtual void OnInit() override
	{
		currentChild = children.begin();
	}

	// Called when the selector finishes
	virtual void OnExit(Status status) override
	{
		currentChild = children.begin();
	}

	// Called every tick
	Status update(Hunter* owner) override
	{
		while (true)
		{
			Status s = (*currentChild)->Tick(owner);
			if (s != Status::Failure)
				return s;
			if (++currentChild == children.end())
				return Status::Failure;
		}
	}
};

// Decorators could either - transform the result it recieved from the child, halt the execution of the child or repeat the ticking of the child
class Decorator : public Behaviour
{
public:
	void addChild(Behaviour* _child) { child = _child; }

protected:
	Behaviour* child;
};

// The inverter is a type of decorator that inverts the result of the child
class Inverter : public Decorator
{
protected:
	virtual Status update(Hunter* owner) override {
		Status childStatus = child->Tick(owner);

		switch (childStatus)
		{
		case Status::Failure: // If the result is a failure...
			return Status::Success; //  It turns it into success

		case Status::Success: // If the result is a sucess...
			return Status::Failure; // It turns it into failure
		default:
			return childStatus;
		}
	}
};

class MoveToAction : public Behaviour
{
	Status update(Hunter* owner) override;
};

class FindNearPreyQuery : public Behaviour
{
	Status update(Hunter* owner) override;
};

class KillPrey : public Behaviour
{
	Status update(Hunter* owner) override;
	bool setPreyDead = false;
};

class HunterRoam : public Behaviour
{
	Status update(Hunter* owner) override;
};

class HunterRest : public Behaviour
{
	Status update(Hunter* owner) override;
};

class HunterFindHome : public Behaviour
{
	Status update(Hunter* owner) override;
};

class HunterFollowPath : public Behaviour
{
	Status update(Hunter* owner) override;
};
