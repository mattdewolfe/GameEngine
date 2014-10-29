#ifndef TIMER_H
#define TIMER_H

#include <time.h>

class Timer
{
private:
	time_t current;
public:
	Timer();
	~Timer();

	bool Init();
	// Start/restart the timer
	void Start();
	// Pause the timer

	void Update();

	void Pause();
	// Resets elapsed time to 0
	void Reset();
	
	float GetDeltaTime();
};

#endif