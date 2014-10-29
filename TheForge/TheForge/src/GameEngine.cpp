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
	
	/*camera = new Camera();
	if (!camera)
	{
		return false;
	}*/

	graphicsManager = new GraphicsManager();
	if (!graphicsManager)
	{
		return false;
	}

	initResult = graphicsManager->Init(screenWidth, screenHeight, hWnd, camera);
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

	/*s
	debugManager = new DebugManager();
	*/
	
	timer = Timer();
	timer.Init();
	framesPerSecond = 0;

	isPaused = false;

	return initResult;
}

// Initialize window and windows elements
bool GameEngine::InitializeWindows(int _width, int _height)
{
	ApplicationHandle = this;

    // this struct holds information for the window class
    WNDCLASSEX wc;

    // clear out the window class for use
    ZeroMemory(&wc, sizeof(WNDCLASSEX));

    // fill in the struct with the needed information
    wc.cbSize = sizeof(WNDCLASSEX);
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
    wc.lpszClassName = L"WindowClass1";

    // register the window class
    RegisterClassEx(&wc);

    // create the window and use the result as the handle
    hWnd = CreateWindowEx(NULL,
                          L"WindowClass1",    // name of the window class
                          L"The Forge Engine",   // title of the window
                          WS_OVERLAPPEDWINDOW,    // window style
                          300,    // x-position of the window
                          300,    // y-position of the window
                          500,    // width of the window
                          400,    // height of the window
                          NULL,    // we have no parent window, NULL
                          NULL,    // we aren't using menus, NULL
                          hInstance,    // application handle
                          NULL);    // used with multiple windows, NULL

    // display the window on the screen
    ShowWindow(hWnd, 1);

	// the following code is from a tutorial, likely needs to be deleted/reworked
	// it deals with the WindowProc function, which deals with input events from the window. 
	// still need to research more into the importance of this function, and if/where we need to relocate it

    //// enter the main loop:

    //// this struct holds Windows event messages
    //MSG msg;

    //// wait for the next message in the queue, store the result in 'msg'
    //while(GetMessage(&msg, NULL, 0, 0))
    //{
    //    // translate keystroke messages into the right format
    //    TranslateMessage(&msg);

    //    // send the message to the WindowProc function
    //    DispatchMessage(&msg);
    //}

    //// return this part of the WM_QUIT message to Windows
    //return msg.wParam;
	return true;
}

//handles the main loop.
void GameEngine::Run()
{
	//** DEMONSTRATION of sustainability.

	MSG message;
	ZeroMemory(&message, sizeof(MSG));

	bool isFinished, isUpdatable;
	
	isFinished = false;
	while(!isFinished)
	{
		if (PeekMessage(&message, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&message);
			DispatchMessage(&message);
		}

		if (message.message == WM_QUIT)
		{
			isFinished = true;
		}
		else
		{
			isUpdatable = Update();
			if(!isUpdatable)
			{
				isFinished = true;
			}
		}

		if(inputManager->Quit())
		{
			isFinished = true;
		}
	}

	return;
}

// Update game world (based on frame time)
// In other words, our game loop.
bool GameEngine::Update()
{
	float tick;

	if(isPaused)
	{
		return true;
	}

	timer.Update();
	tick = timer.GetDeltaTime();

	inputManager->Update(tick);
	eventManager->Update(tick);
	audioManager->Update(tick);
	scriptManager->Update(tick);
	RenderFrame();
	
	return true;
}

// Renders the next frame
void GameEngine::RenderFrame()
{
	graphicsManager->D3D_Render();
}
// Hault update calls by engine
void GameEngine::Pause()
{
}
// Called at termination, free memory, clear pointers, etc
void GameEngine::Shutdown()
{
	graphicsManager->Shutdown();
}
// Shutdown calls specific to window(s)
void GameEngine::ShutDownWindows()
{

}
// System for passing calls to other classes
LRESULT CALLBACK  GameEngine::MessageHandler(HWND _hwnd, UINT _umsg, WPARAM _wparam, LPARAM _lparam)
{
	switch(_umsg)
	{
	//input.
	case WM_KEYDOWN:
		inputManager->KeyDown((unsigned int)_wparam);
		break;
	case WM_KEYUP:
		inputManager->KeyUp((unsigned int)_wparam);
		break;
	//effectively, clicking the closer arrow.
	case WM_DESTROY:
		 PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(_hwnd, _umsg, _wparam, _lparam);
		break;
	}
}
// Used to determine time between frames
void GameEngine::CalculateFPS()
{

}

// DELETE? temporary window handling funcion
// this is from a tutorial, intended as a main loop. Handles window events (like clicking the red x to close a window, and maybe resizing?)
LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    // sort through and find what code to run for the message given
    switch(message)
    {
        // this message is read when the window is closed
        case WM_DESTROY:
            {
                // close the application entirely
                PostQuitMessage(0);
                return 0;
            } 
			break;
		default:
		{
			return ApplicationHandle->MessageHandler(hWnd, message, wParam, lParam);
		}
    }

    // Handle any messages the switch statement didn't
    return DefWindowProc (hWnd, message, wParam, lParam);
}

