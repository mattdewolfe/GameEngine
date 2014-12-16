#include "GameEngine.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR pScmdline, int iCmdshow)
{
	GameEngine* engine;
	engine = new GameEngine();

	if (engine->Init(hInstance) == false)
	{
		return 0;
	}

	engine->Run();

	engine->Shutdown();
	
	delete engine;
	engine = NULL;

	return 0;
}