#ifndef EVENTS_H
#define EVENTS_H

#include "EventManager.h"

class EventData_TimerPaused : public BaseEventData
{
public:
	static const EventType eventType;

	explicit EventData_TimerPaused() { }

	virtual const EventType& VGetEventType() const { return eventType; }
	virtual IEventDataPtr VCopy() { return IEventDataPtr(this); }
	virtual const char* GetName() const { return "EventData_TimerPaused"; }
	virtual void VSerialize() const { std::printf(this->GetName()); }
};

#endif