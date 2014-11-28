#include "Timer.h"

Timer::Timer()
{

}

void Timer::Start()
{

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

	std::shared_ptr<EventData_TimerPaused> ptrTimerPaused (
	new EventData_TimerPaused() );

	_events->VQueueEvent(ptrTimerPaused);
	//_events->VTriggerEvent(ptrTimerPaused);

	return true;
}

// Temp solution of passing in event system until 
// we decide on handling as global/static
void Timer::Pause(EventManager* _events)
{
	_events->VQueueEventByType(EVENT_Timer_Paused);
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
