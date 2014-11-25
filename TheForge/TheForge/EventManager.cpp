#include "Events\EventManager.h"

EventManager::EventManager(char const* const _ptrName, bool _setAsGlobal) :
	IEventManager(_ptrName, _setAsGlobal)
{
	activeQueue = 0;
}

bool EventManager::VAddListener(const EventListenerDelegate& _eventDelegate, 
		const EventType& _type)
{
	// Find or create the event listener
	EventListenerList& eventListenerList = eventListeners[_type];
	for (auto it = eventListenerList.begin(); it != eventListenerList.end(); it++)
	{
		if (_eventDelegate == (*it))
		{
			// If we are here the system is attempting to register a delegate twice
			return false;
		}
	}
	// If we get here, the delegate was not found and can be added to the list
	eventListenerList.push_back(_eventDelegate);
	return true;
}
	
bool EventManager::VARemoveListener(const EventListenerDelegate& _eventDelegate, 
		const EventType& _type)
{
	bool success = false;
	// Search through listeners for the specified event type
	auto findIt = eventListeners.find(_type);
	if (findIt != eventListeners.end())
	{
		EventListenerList& listeners = findIt->second;
		// Move through listeners to find target delegate
		for (auto it = listeners.begin(); it != listeners.end(); it++)
		{
			if (_eventDelegate == (*it))
			{
				listeners.erase(it);
				success = true;
				// We can break out now since the same delegate should not
				// be registered to the same event type more than once
				break;
			}
		}
	}
	return success;
}
	
bool EventManager::VTriggerEvent(const IEventDataPtr& _ptrEvent)
{
	bool processed = false;
	// Find the target event 
	auto findIt = eventListeners.find(_ptrEvent->VGetEventType());
	if (findIt != eventListeners.end())
	{
		const EventListenerList& eventListenerList = findIt->second;
		// Move through event listener list to find event
		for (EventListenerList::const_iterator it = eventListenerList.begin();
			it != eventListenerList.end(); it++)
		{
			EventListenerDelegate listener = (*it);
			listener(_ptrEvent);
			processed = true;
		}
	}
	return processed;
}
	
bool EventManager::VQueueEvent(const IEventDataPtr& _ptrEvent)
{
	auto findIt = eventListeners.find(_ptrEvent->VGetEventType());
	if (findIt != eventListeners.end())
	{
		queues[activeQueue].push_back(_ptrEvent);
		return true;
	}
	else
	{
		return false;
	}
}

bool EventManager::VTerminateAll(const EventType& _type)
{

}

void EventManager::VUpdate(unsigned long _maxMilliseconds = 9999)
{

}