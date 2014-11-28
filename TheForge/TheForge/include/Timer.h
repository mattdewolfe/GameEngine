#ifndef TIMER_H
#define TIMER_H

#include <time.h>
#include "Events\EventManager.h"

class Timer
{
private:
	time_t current;
public:
	Timer();
	~Timer();

	bool Init(EventManager* _events);
	// Start/restart the timer
	void Start();
	// Pause the timer

	void Update();

	void Pause();
	void TimerPausedDelegate(IEventDataPtr _ptrEventData);
	// Resets elapsed time to 0
	void Reset();
	
	float GetDeltaTime();
};

#endif