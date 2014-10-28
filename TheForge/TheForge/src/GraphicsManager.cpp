#include "GraphicsManager.h"

GraphicsManager::GraphicsManager()
{

}

GraphicsManager::~GraphicsManager()
{

}

bool GraphicsManager::Init(int, int, HWND, Camera*)
{
	return true;
}

void GraphicsManager::Shutdown()
{

}

void GraphicsManager::EngineRender()
{

}

void GraphicsManager::D3D_Render()
{

}

// To alter -> Would it make more sense to only pass pointers to meshes rather than entire entities?
void GraphicsManager::AddToRenderList(GameEntity* _e)
{

}

void GraphicsManager::RemoveFromRenderList(GameEntity* _e)
{

}

