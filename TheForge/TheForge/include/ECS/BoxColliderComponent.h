#ifndef BOXCOLLIDERCOMPONENT_H
#define BOXCOLLIDERCOMPONENT_H

#include "IGameComponent.h"

class BoxColliderComponent : public IGameComponent
{
public:
	// Create a basic box collider
	BoxColliderComponent();
	// Specifiy size and position of colider (dimensions x = width, y = height, z = depth)
	BoxColliderComponent(float3 _center, float3 _dimensions);
	BoxColliderComponent(float3 _center, float _width, float _height, float _depth);
	~BoxColliderComponent();
	// init will be called by constructor
	virtual bool Init();
	virtual void Destroy();
	virtual void Update(float _deltaTime);
	// Called if debug rendering is enabled
	void DebugRender();
	// Get a reference to this collider to be passed into collision checks by engine
	BoxColliderComponent* GetCollider() { return this; }
private:
	float3 center;
	// X = width, Y = height, Z = depth
	float3 dimensions;
};

#endif