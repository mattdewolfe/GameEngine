#include "GameEngine.h"

GameEngine::GameEngine()
{

}

GameEngine::~GameEngine()
{ }

// Initialize engine classes and resources
bool GameEngine::Init()
{
	// Handle each bool return from individual system
	// initializations. If ever false the engine has failed 
	// to init a given system
	bool initResult;
	
	// Setup window, at size 0, 0 to start
	int screenWidth, screenHeight;
	screenWidth = 0;
	screenHeight = 0;
	InitializeWindows(0, 0);

	// Setup files to be loaded by resource loader

	inputManager = new InputManager();
	if (!inputManager)
	{
		return false;
	}
	initResult = inputManager->Init();
	
	camera = new Camera();
	if (!camera)
	{
		return false;
	}

	graphicsManager = new GraphicsManager();
	if (!graphicsManager)
	{
		return false;
	}

	initResult = graphicsManager->Init(screenWidth, screenHeight, hwnd, camera);
	if (initResult==false)
	{
		return false;
	}

	audioManager = new AudioManager;
	if (!audioManager)
	{
		return false;
	}

	initResult = audioManager->Init();
	if(initResult==false)
	{
		return false;
	}

	eventManager = new EventManager;
	if (!eventManager)
	{
		return false;
	}

	initResult = eventManager->Init();
	if (initResult==false)
	{
		return false;
	}

	scriptManager = new ScriptManager;
	if (!scriptManager)
	{
		return false;
	}

	initResult = scriptManager->Init();
	if (initResult==false)
	{
		return false;
	}

	debugManager = new DebugManager();
	
	timer.Init();

	framesPerSecond = 0;

	return initResult;
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

