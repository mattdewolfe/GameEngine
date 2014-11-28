#ifndef EVENT_DATA_H
#define EVENT_DATA_H

#include <memory>
#include <iostream> 
#include "Events\FastDelegate.h"
#include "Events\FastDelegateBind.h"

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
	virtual IEventDataPtr VCopy() const = 0;
	virtual const char* GetName() const = 0;
};

class BaseEventData : public IEventData
{
	const float timeStamp;

public:
	// Use of explicit to prevent the compiler from converting
	// other variable types to the one our constructor requires
	explicit BaseEventData(const float _timeStamp = 0.0f) :
	timeStamp(_timeStamp) {};
	virtual ~BaseEventData() {}

	// Get the type of event
	virtual const EventType& VGetEventType() const = 0;
	// Get the timestamp from this events creation
	float GetTimeStamp() const { return timeStamp; }
	// Serializing (for network use, for now for debug lines)
	virtual void VSerialize() const {}
};

#endif