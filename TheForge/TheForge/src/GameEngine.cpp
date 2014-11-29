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
	
	eventManager = new EventManager("eventSys", true);
	if (!eventManager)
	{
		return false;
	}

	// Setup files to be loaded by resource loader
	resourceLoader = new ResourceLoader();
	if(!resourceLoader)
	{
		return false;
	}

	initResult = resourceLoader->Init();
	if (initResult == false)
	{
		return false;
	}

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

	timer = Timer();
	timer.Init(eventManager);
	
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
	// RYAN - See below
	// Passing in the event manager for the time being
	// This is a dirty method that will be resolved upon global access decision
	// Attempted using the books Static Get method, and it Static Sucks.
	// This pause should fire the timer paused event once, and print the 
	// event data type to the output window (of VS)
	timer.Pause(eventManager);
	
	
	inputManager->Update(tick);
	eventManager->VUpdate();
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
	// Call shutdown on all game systems
	// in reverse order of intialization
	scriptManager->Shutdown();
	audioManager->Shutdown();
	graphicsManager->Shutdown();
	inputManager->Shutdown();
	resourceLoader->Shutdown();
	
	// Free memory and delete pointers
	SAFE_DELETE(scriptManager);
	SAFE_DELETE(eventManager);
	SAFE_DELETE(audioManager);
	SAFE_DELETE(graphicsManager);
	SAFE_DELETE(camera);
	SAFE_DELETE(inputManager);
	SAFE_DELETE(resourceLoader);
}
// Shutdown calls specific to window(s)
void GameEngine::ShutDownWindows()
{

}
// System for passing calls to other classes
LRESULT CALLBACK GameEngine::MessageHandler(HWND _hwnd, UINT _umsg, WPARAM _wparam, LPARAM _lparam)
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
	// TODO: look into capturing the mouse position for tracking movement outside of game window
	case WM_MOUSEMOVE:
		inputManager->MouseMove(GET_X_LPARAM(_lparam), GET_Y_LPARAM(_lparam));
		break;
	// TODO: accept input from all mouse buttons, not just left and right. Sort them in a proper data structure
	case WM_LBUTTONDOWN:
		inputManager->MouseButtonDown(0);
		break;
	case WM_LBUTTONUP:
		inputManager->MouseButtonUp(0);
		break;
	case WM_RBUTTONDOWN:
		inputManager->MouseButtonDown(1);
		break;
	case WM_RBUTTONUP:
		inputManager->MouseButtonUp(1);
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

// Handles window events. Need to research proper use of this function
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