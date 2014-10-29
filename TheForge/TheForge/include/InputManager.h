#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

class InputManager
{
private:
	bool isQuit;
public:
	InputManager();
	~InputManager();

	bool Init();
	void Update(float _dt);
	void Shutdown();

	//simple key press events.
	bool KeyDown(unsigned int _key);
	bool KeyUp(unsigned int _key);

	bool Quit();
};

#endif
