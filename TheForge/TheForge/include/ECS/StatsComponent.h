#ifndef STATSCOMPONENT_H
#define STATSCOMPONENT_H

#include <string>
#include "IGameComponent.h"
#include "../Script/XMLScriptManager.h"

// Component that stores gameplay variables for an entity
class StatsComponent : public IGameComponent
{
public: 
	StatsComponent(char* _statClass) : IGameComponent(STATS)
	{
		health = 0;
		statClass = _statClass;
	}
	~StatsComponent() { }
	// Store the name of the xml stat class this was initialized with
	char* statClass;

	bool Init() { return true; };
	void Destroy() { };
	void Update(float _deltaTime) { };

	int GetHealth() { return health; }
	void SetHealth(int _var) { health = _var; }
	// Pass in the value to add to current health, and check if character is dead
	void AlterHealth(int _val)
	{ 
		health += _val; 
		if (health <= 0)
			isAlive = false;
	}
	// Get/Set move speed value
	float GetSpeed() { return speed; }
	void SetSpeed(float _val) { speed = _val; }
	// Get/Set isAlive flag
	bool GetIsAlive() { return isAlive; }
	void SetIsAlive(bool _val) { isAlive = _val; }
	// Get/Set this characters name
	std::string GetName() { return name; }
	void SetName(std::string _var) { name = _var; }

	private:
		float speed;
		int health;
		bool isAlive;
		std::string name;
};
#endif