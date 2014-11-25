#ifndef EVENT_MANAGER_H
#define EVENT_MANAGER_H

#include <list>
#include <map>
#include <memory>
#include "EventData.h"

// Interface for all event managers
class IEventManager
{
public:
	explicit IEventManager(const char* _ptrName, bool _setAsGlobal)
	{
		
	}

	virtual ~IEventManager() { }

	// Register a delegate function and event pair. The function should be called
	// when the event is triggered
	virtual bool VAddListener(const EventListenerDelegate& _eventDelegate, 
		const EventType& _type) = 0;
	// Remove a delegate function and event pair from the list
	virtual bool VRemoveListener(const EventListenerDelegate& _eventDelegate, 
		const EventType& _type) = 0;
	// Fire the specified event immidiately, bypassing event queue. All registered
	// delegate functions will be called
	virtual bool VTriggerEvent(const IEventDataPtr& _ptrEvent) const = 0;
	// Pushes the specified event onto the queue and will call it
	// if there is enough time during the next tick
	virtual bool VQueueEvent(const IEventDataPtr& _ptrEvent) = 0;
	// Removes all instances of a specified event from the queue and will
	// not call any registered delegates
	virtual bool VTerminateAll(const EventType& _type) = 0;
	// Process queued messages, optionally limit amount of time system
	// can spend processing messages
	virtual void VUpdate(unsigned long _maxMs = 9999) = 0;
	// Get a reference to our global event manager, as we should only have
	// one that is available across the entire engine
	static IEventManager* Get();
};

// Define our global event manager

// Define the number of queues we want to have in our manager
const unsigned int EM_NUMBER_OF_QUEUES = 2;

class EventManager : public IEventManager
{
	// A list of all event listeners for this manager
	typedef std::list<EventListenerDelegate> EventListenerList;
	// A map of event types, and the matching list of delegates registered to that event
	typedef std::map<EventType, EventListenerList> EventListenerMap;
	// A list of EventData pointers which we use for our queue of messages
	typedef std::list<IEventDataPtr> EventQueue;

	EventListenerMap eventListeners;
	EventQueue queues[EM_NUMBER_OF_QUEUES];
	// index to the queue we are actively processing
	int activeQueue;
	
public:
	explicit EventManager(const char* _ptrName, bool _setAsGlobal);
	virtual ~EventManager() { }

	virtual bool VAddListener(const EventListenerDelegate& _eventDelegate, 
		const EventType& _type);
	
	virtual bool VARemoveListener(const EventListenerDelegate& _eventDelegate, 
		const EventType& _type);
	
	virtual bool VTriggerEvent(const IEventDataPtr& _ptrEvent);
	
	virtual bool VQueueEvent(const IEventDataPtr& _ptrEvent);

	virtual bool VTerminateAll(const EventType& _type);

	virtual void VUpdate(unsigned long _maxMilliseconds = 9999);

};

#endif
