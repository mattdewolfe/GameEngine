#ifndef GAMEENTITY_H
#define GAMEENTITY_H

#include <map>
#include <memory>

#include "IGameComponent.h"

typedef std::map<GameComponentType, IGameComponentPtr> GameComponentMap;

class GameEntity

{
public:
	GameEntity();
	~GameEntity();

	// Should iteratre through all components and update
	void Update(float _deltaTime);

	// Add a component to this entity
	void AddComponent(IGameComponent* _component);
	// Attempt to remove a component by its component type
	bool RemoveComponentByType(GameComponentType _type);
	// Attempt to remove a component by its game ID
	bool RemoveComponentByID(int _ID);
	// Attempt to remove a specific component
	bool RemoveComponent(IGameComponent* _component);
	// Free memory held by components
	void Shutdown();

	// Getters and setters
	void SetPosition(float x, float y, float z);
	float3 GetPosition();

	void SetRotation(float x, float y, float z);
	float3 GetRotation();

	void SetVelocity(float x, float y, float z);
	float3 GetVelocity();

protected:
	float3 _position;
	float3 _rotation;
	float3 _velocity;
};

#endif