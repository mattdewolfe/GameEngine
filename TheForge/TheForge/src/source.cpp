#include "GameEngine.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR pScmdline, int iCmdshow)
{
	GameEngine* engine;
	engine = new GameEngine();
	if (engine->Init() == false)
	{
		return 0;
	}
	//engine->Run();

	// DELETE used for Debug, replace with a proper game loop
	engine->RenderFrame();
	while (true) {}

	engine->Shutdown();
	delete engine;
	engine = 0;

	return 0;
}