#ifndef MESHCOMPONENT_H
#define MESHCOMPONENT_H

#include "IGameComponent.h"

class MeshComponent : public IGameComponent
{
public:
	// Create component with specified file
	MeshComponent(char* _fileName);
	~MeshComponent();

	// Load and init should be called by constructor in order to read mesh
	// and store vertices into array
	bool LoadFile(char* _fileName);
	virtual bool Init();
	virtual void Destroy();
	virtual void Update(float _deltaTime);
	// Render to be called at end of update
	void Render();

private:
	int verts;
	float3* vertices[];
};

#endif