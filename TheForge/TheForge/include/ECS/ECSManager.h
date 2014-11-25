#ifndef ECSMANAGER_H
#define ECSMANAGER_H

#include <list>
#include "GameEntity.h"
#include "IGameComponent.h"

class ECSManager
{
public:
	ECSManager();
	~ECSManager();
	
	std::list<GameEntity*> entities;

	// Add an entity to the system
	void AddEntity(GameEntity* _entity);
	// Attempt to remove an entity, based on the given entity
	bool RemoveEntity(GameEntity* _entity);
	// Attempt to remove an entity, based on its game ID
	bool RemoveEntityByID(int _ID);
	// Update all entities (in turn updating all their components)
	void Update(float _deltaTime);
	// Create a given component type and add it to all entities
	void CreateComponentTypeAll(GameComponentType _type);
	// Remove a given type of component from all entites
	void RemoveComponentTypeAll(GameComponentType _type);
	// Add/Remove a component type from a specific entity
	void CreateComponentTypeEntity(GameComponentType _type, GameEntity* _entity);
	void RemoveComponentTypeEntity(GameComponentType _type, GameEntity* _entity);
};

#endif
