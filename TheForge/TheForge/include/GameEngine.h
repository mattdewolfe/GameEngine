#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include <Windows.h>
#include <WindowsX.h>

#include "AudioManager.h"
#include "ECS\ECSManager.h"
#include "GraphicsManager.h"
#include "InputManager.h"
#include "ResourceLoader.h"
#include "EventHandler.h"

class GameEngine
{
public:

	GameEngine();
	~GameEngine();

	// Initialize engine classes and resources
	bool Init();
	// Initialize window with width height values
	bool InitializeWindows(int, int);
	// Update game world (based on frame time)
	void Update(float deltaTime);
	// Renders the next frame
	void RenderFrame();
	// Hault update calls by engine
	void Pause();
	// Called at termination, free memory, clear pointers, etc
	void Shutdown();
	// Shutdown calls specific to window(s)
	void ShutDownWindows();
	// System for passing calls to other classes
	void MessageHandler();
	// Used to determine time between frames
	void CalculateFPS();

private:
	LPCWSTR _applicationName;
	HINSTANCE _hinstance;
	HWND _hwnd;
	/*
	AudioManager* audioManager;
	ECSManager* ecsManager;
	GraphicsManager* graphicsManager;
	InputManager* inputManager;
	EventHandler* eventHandler;
	resourceLoader* resourceLoader;
	*/

	float framesPerSecond;

};

#endif