#ifndef EVENTS_H
#define EVENTS_H

#include "EventManager.h"

class EventData_TimerPaused : public BaseEventData
{
public:

	EventData_TimerPaused() : BaseEventData(EVENT_Timer_Paused, 0.0f) { }
		
	float VGetTimeStamp() { return 0.0f; }
	const EventType& VGetEventType() const { return eventType; }
	const char* VGetName() { return "EventData_TimerPaused"; }
	void VSerialize() { DBOUT(this->VGetName()); }
};

#endif