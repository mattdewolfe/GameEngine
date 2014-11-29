#ifndef EVENT_DATA_H
#define EVENT_DATA_H

#include <memory>
#include <Windows.h>
#include <iostream>
#include <sstream> 
#include "Events\FastDelegate.h"
#include "Events\FastDelegateBind.h"

// Macro for tracing event data names into output window
#define DBOUT( s )            \
{                             \
   std::wostringstream os_;    \
   os_ << s << "\n";                   \
   OutputDebugStringW( os_.str().c_str() );  \
}

class IEventData;
// Typedef a shared pointer handle for ease
typedef std::shared_ptr<IEventData> IEventDataPtr;

// As based on Fast Delegate code //
void Delegate(IEventDataPtr pEventData);

typedef fastdelegate::FastDelegate1<IEventDataPtr> EventListenerDelegate;

// Should store all types of events we plan to listen for
// Bound to be a long list
enum EventType
{
	EVENT_Object_Moved,
	EVENT_Object_Created,
	EVENT_Object_Destroy, 
	EVENT_Timer_Paused
};

class IEventData
{
public:
	virtual const EventType& VGetEventType() const = 0;
	virtual float VGetTimeStamp() const = 0;
	virtual void VSerialize() const = 0;
	virtual const char* VGetName() const = 0;
};

class BaseEventData : public IEventData
{
public:
	const float timeStamp;
	const EventType eventType;
	// Use of explicit to prevent the compiler from converting
	// other variable types to the one our constructor requires
	BaseEventData(EventType _type, const float _timeStamp = 0.0f) :
	timeStamp(_timeStamp),
	eventType(_type) {};
	virtual ~BaseEventData() {}


	// Get the type of event
	const EventType& VGetEventType() const { return eventType; }
	// Get the timestamp from this events creation
	float VGetTimeStamp() const { return timeStamp; }
	// Serializing (for network use, for now for debug lines)
	void VSerialize() const { DBOUT("base"); }
	const char* VGetName() const { return "base"; }
};

#endif