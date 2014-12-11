#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#include <vector>
#include <Windows.h>

// TODO: As of right now the InputManager class always stores information for exactly one keyboard and mouse
// In the future, look into making keyboard and mouse classes, and having the ability to add multiple instances of them

struct KeyState
{
	KeyState() : previousKeyState(false), currentKeyState(false), debugKeyState(false) {}
	// I've included three states. Previous, current, and debugKeyState.
	// the difference betwen currentState and debugKeyState is that currentState is set to the value of debugKeyState inside 
	// the inputManager Update class, whereas debugKeyState is set by the windows MessageHandler in GameEngine.cpp
	// This might be unnecessary, but I don't know how the timing of the windows MessageHandler and our GameEngine
	// Update calls interact, and I need to ensure that the perviousState and currentState changes in sync with Update calls
	bool previousKeyState;
	bool currentKeyState;
	bool debugKeyState;
};

struct MousePositionAxis
{
	MousePositionAxis() : previousPos(0), currentPos(0), debugPos(0) {}
	int previousPos, currentPos, debugPos;
};

class InputManager
{
private:
	bool isQuit;
	// used to track buttons who changed state last update. This is to avoid looping through every button
	// TODO: surely there is a better system than this, look into alternatives
	std::vector<unsigned int> recentlyToggled;
	KeyState* keyStates;	
	MousePositionAxis mouseX, mouseY;
	// using the KeyState struct for mouse is confusing (due to the name) maybe rename the struct?
	std::vector<KeyState> mouseButtons;
	// TODO: For some reason I can't create an object of HKL type, which means I can't convert from characters to Virtual Keys
	// Find out why visual studio is so pissed off by the HKL type
	HKL inputLocaleIdentifier;

	
public:
	InputManager();
	~InputManager();

	bool Init();
	void Update(float _dt);
	void Shutdown();

	//simple key press events.
	void KeyDown(unsigned int _key);
	void KeyUp(unsigned int _key);
	void MouseMove(unsigned int _x, unsigned int _y);
	void MouseButtonDown(int _button);
	void MouseButtonUp(int _button);

	// returns true when down, false when up
	bool GetKey(unsigned int _key);
	bool GetKey(char _c);
	// returns true on the first frame the key is pressed down
	bool GetKeyDown(unsigned int _key);
	bool GetKeyDown(char _c);
	// returns true on the first frame the key is released
	bool GetKeyUp(unsigned int _key);
	bool GetKeyUp(char _c);
	// TODO: change from inividual mouse buttons methods into one unified. Requires mouse buttons to be stored in a data structure
	int GetMouseX();	
	int GetMouseY();
	bool GetMouseButton(int _button);
	bool GetMouseButtonDown(int _button);
	bool GetMouseButtonUp(int _button);


	bool Quit();

	// array representing each key of a keyboard
	
};



#endif
