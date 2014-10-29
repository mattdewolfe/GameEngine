#ifndef TIMER_H
#define TIMER_H

class Timer
{
public:
	Timer();
	~Timer();

	bool Init();
	// Start/restart the timer
	void Start();
	// Pause the timer
	void Pause();
	// Resets elapsed time to 0
	void Reset();
	
};

#endif