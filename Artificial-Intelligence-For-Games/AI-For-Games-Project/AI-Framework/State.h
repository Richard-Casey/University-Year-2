#pragma once
class Prey;
class Hunter;

class State
{
public:
	virtual void Enter(Prey* owner) {};
	virtual State* Execute(Prey*) = 0;
	BaseEntity* hunter;
	BaseEntity* prey;
	BaseEntity* getHunter() { return hunter; }
	BaseEntity* getPrey() { return prey; }
};

class RestState : public State
{
public:
	void Enter(Prey* owner);
	State* Execute(Prey*);
	void Enter(Hunter* owner);
	State* Execute(Hunter*);
};

class RunAwaystate : public State
{
public:
	State* Execute(Prey*);
};

class losingHealthState : public State
{
public:
	State* Execute(Prey*);
};

class WonderState : public State
{
public:
	State* Execute(Prey*);
};

class DieState : public State
{
public:
	State* Execute(Prey*);
};

class SeekState : public State
{
public:
	//virtual void Enter(Hunter* owner);
	State* Execute(Hunter*);
};

class CaughtState : public State
{
public:
	void Enter(Prey* owner) override;
	State* Execute(Prey* owner) override;
	void Exit(Prey* owner);
};
