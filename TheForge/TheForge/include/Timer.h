#ifndef TIMER_H
#define TIMER_H

class Timer
{
public:
	// NOTE: changed constructor/destructor/init from function declaration to definition here for debugging, correct this when writing timer.cpp
	// was getting stupid errors, just duct taped it to save myself time
	Timer()
	{
	}
	~Timer()
	{
	}	
	bool Init()
	{
	}
	// Start/restart the timer
	void Start();
	// Pause the timer
	void Pause();
	// Resets elapsed time to 0
	void Reset();
	
};

#endif