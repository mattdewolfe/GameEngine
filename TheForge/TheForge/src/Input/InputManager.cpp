#include "Input\InputManager.h"
#include <vector>


// DELETE THIS
#include <memory>
#include <Windows.h>
#include <iostream>
#include <sstream> 

// Macro for tracing event data names into output window
#define DBOUT( s )            \
{                             \
   std::wostringstream os_;    \
   os_ << s << "\n";                   \
   OutputDebugStringW( os_.str().c_str() );  \
}


InputManager::InputManager()
{
	
}

bool InputManager::Init()
{
	keyStates = new KeyState[256];
	// TODO: typing this out made me sad. Find a better way of storing mouse button information
	// ideally be somewhat dynamic, since different mice have different amounts of buttons
	mouseButtons.push_back(KeyState());
	mouseButtons.push_back(KeyState());
	isQuit = false;
	return true;
}

void InputManager::Update(float _dt)
{
	// update keyboard keyStates. If they are equal, remove them from recentlyUpdated
	for(std::vector<unsigned int>::iterator it = recentlyToggled.begin(); it != recentlyToggled.end(); ) 
	{
		keyStates[*it].previousKeyState = keyStates[*it].currentKeyState;
		keyStates[*it].currentKeyState = keyStates[*it].debugKeyState;
		if (keyStates[*it].previousKeyState == keyStates[*it].currentKeyState)
		{
			it = recentlyToggled.erase(it);
		}
		else
		{
			++it;
		}
	}
	// update mouse trackers
	mouseX.previousPos = mouseX.currentPos;
	mouseX.currentPos = mouseX.debugPos;
	mouseY.previousPos = mouseY.currentPos;
	mouseY.currentPos = mouseY.debugPos;
	// update mouse buttons
	for (int i = 0; i < mouseButtons.size(); ++i)
	{
		mouseButtons[i].previousKeyState = mouseButtons[i].currentKeyState;
		mouseButtons[i].currentKeyState = mouseButtons[i].debugKeyState;
	}
}

void InputManager::KeyDown(unsigned int _key)
{
	keyStates[_key].debugKeyState = true;
	recentlyToggled.push_back(_key);
}

void InputManager::KeyUp(unsigned int _key)
{
	keyStates[_key].debugKeyState = false;
	recentlyToggled.push_back(_key);
}

void InputManager::MouseMove (unsigned int _x, unsigned int _y)
{
	mouseX.debugPos = _x;
	mouseY.debugPos = _y;
}

void InputManager::MouseButtonDown (int _button)
{
	mouseButtons[_button].debugKeyState = 1;
}

void InputManager::MouseButtonUp (int _button)
{
	mouseButtons[_button].debugKeyState = 0;
}

bool InputManager::GetKey(unsigned int _key)
{
	return keyStates[_key].currentKeyState;
}

bool InputManager::GetKeyDown(unsigned int _key)
{
	return (keyStates[_key].currentKeyState && !keyStates[_key].previousKeyState);
}

bool InputManager::GetKeyUp(unsigned int _key)
{
	return (!keyStates[_key].currentKeyState && keyStates[_key].previousKeyState);
}

int InputManager::GetMouseX ()
{
	return mouseX.currentPos;
}

int InputManager::GetMouseY ()
{
	return mouseY.currentPos;
}

bool InputManager::GetMouseButton (int _button)
{
	return mouseButtons[_button].currentKeyState;
}

bool InputManager::GetMouseButtonDown (int _button)
{
	return (mouseButtons[_button].currentKeyState && !mouseButtons[_button].previousKeyState);
}

bool InputManager::GetMouseButtonUp (int _button)
{
	return (!mouseButtons[_button].currentKeyState && mouseButtons[_button].previousKeyState);
}

bool InputManager::Quit()
{
	return isQuit;
}

void InputManager::Shutdown()
{

}

InputManager::~InputManager()
{

}


