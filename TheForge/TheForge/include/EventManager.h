#ifndef EVENTMANAGER_H
#define EVENTMANAGER_H

class EventManager
{
public:
	EventManager();
	~EventManager();

	bool Init();
	void Update(float _dt);
	void Shutdown();
};

#endif
