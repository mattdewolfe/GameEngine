#include "Input\InputManager.h"

InputManager::InputManager()
{
	
}

bool InputManager::Init()
{
	isQuit = false;
	return true;
}

void InputManager::Update(float _dt)
{
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

bool InputManager::KeyDown(unsigned int _key)
{
	if(_key == 0x1B)
		isQuit = true;

	return false;
}

bool InputManager::KeyUp(unsigned int _key)
{
	return false;
}
