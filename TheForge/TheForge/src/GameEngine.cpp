#include "GameEngine.h"

GameEngine::GameEngine()
{

}

GameEngine::~GameEngine()
{ }

// Initialize engine classes and resources
bool GameEngine::Init()
{
	return true;
}
// Initialize window and windows elements
bool GameEngine::InitializeWindows(int _width, int _height)
{
	return true;
}
// Update game world (based on frame time)
void GameEngine::Update(float _deltaTime)
{

}
// Renders the next frame
void GameEngine::RenderFrame()
{

}
// Hault update calls by engine
void GameEngine::Pause()
{

}
// Called at termination, free memory, clear pointers, etc
void GameEngine::Shutdown()
{

}
// Shutdown calls specific to window(s)
void GameEngine::ShutDownWindows()
{

}
// System for passing calls to other classes
void GameEngine::MessageHandler()
{

}
// Used to determine time between frames
void GameEngine::CalculateFPS()
{

}

