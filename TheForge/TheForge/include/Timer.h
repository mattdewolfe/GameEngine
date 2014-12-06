#ifndef TIMER_H
#define TIMER_H

#include <time.h>
#include "Events\EventManager.h"

class Timer
{
private:
	time_t current;
	bool isPaused;
public:
	Timer();
	~Timer();

	bool Init(EventManager* _events);
	// Start/restart the timer
	void Start();
	void Update();
	// Pause the timer
	void Pause(EventManager* _events);
	// Delegate function for when timer is paused, used temporarily to test 
	void TimerPausedDelegate(IEventDataPtr _ptrEventData);
	// Resets elapsed time to 0
	void Reset();
	float GetDeltaTime();
};

#endif