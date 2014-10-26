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

protected:/*
	Vector3 _position;
	Vector3 _rotation;
	Vector3 _velocity;*/
};

#endif