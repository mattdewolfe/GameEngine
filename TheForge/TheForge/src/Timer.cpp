#include "Timer.h"

Timer::Timer() : isPaused(false)
{

}

void Timer::Start()
{
	isPaused = false;
}

void Timer::Update()
{
	current = time(NULL);
}

bool Timer::Init(EventManager* _events)
{
	EventListenerDelegate delegateFunction = 
		fastdelegate::MakeDelegate(this, &Timer::TimerPausedDelegate);
		
	_events->VAddListener(delegateFunction, 
		EVENT_Timer_Paused);

	return true;
}

// Temp solution of passing in event system until 
// we decide on handling as global/static
void Timer::Pause(EventManager* _events)
{
	// If timer is not paused, pause it and fire event
	if (isPaused == false)
	{
		isPaused = true;
		
		std::shared_ptr<EventData_TimerPaused> ptrTimerPaused (
		new EventData_TimerPaused() );
		_events->VQueueEvent(ptrTimerPaused);
	}
}

void Timer::TimerPausedDelegate(IEventDataPtr _ptrEventData)
{
	std::shared_ptr<EventData_TimerPaused> ptrCastEventData =
		std::static_pointer_cast<EventData_TimerPaused>(_ptrEventData);

	ptrCastEventData->VSerialize();
}

void Timer::Reset()
{

}

float Timer::GetDeltaTime()
{
	return static_cast<float>(time(NULL) - current);
}

Timer::~Timer()
{

}
