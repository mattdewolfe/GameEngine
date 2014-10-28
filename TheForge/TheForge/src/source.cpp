#include "GameEngine.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR pScmdline, int iCmdshow)
{
	GameEngine* engine;
	engine = new GameEngine();
	if (engine->Init() == false)
	{
		return 0;
	}

	return 0;
}