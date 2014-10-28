#ifndef GRAPHICSMANAGER_H
#define GRAPHICSMANAGER_H

#include <Windows.h>
#include "ECS\GameEntity.h"
#include "Camera.h"

class GraphicsManager
{
public:
	GraphicsManager();
	~GraphicsManager();

	bool Init(int, int, HWND, Camera*);
	void Shutdown();
	void EngineRender();
	void D3D_Render();
	// To alter -> Would it make more sense to only pass pointers to meshes rather than entire entities?
	void AddToRenderList(GameEntity* _e);
	void RemoveFromRenderList(GameEntity* _e);

};
#endif
