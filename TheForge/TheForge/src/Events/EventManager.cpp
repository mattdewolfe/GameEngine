#include "Events\EventManager.h"

EventManager::EventManager(const char* _ptrName, bool _setAsGlobal) :
	IEventManager(_ptrName, _setAsGlobal)
{
	activeQueue = 0;

}

void EventManager::VQueueEventByType(EventType _targetType)
{
	EventListenerMap::iterator findIt = eventListeners.find(_targetType);

	if (findIt != eventListeners.end())
	{
		EventListenerList tempList = findIt->second;
		EventListenerList::iterator thisIt = tempList.begin();
		while (thisIt != tempList.end())
		{
			// Current issue - setting items into the queue by type 
			// triggering. How to?
			//queues[activeQueue].push_back(thisIt);
			thisIt++;
		}
		
	}
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
	
bool EventManager::VRemoveListener(const EventListenerDelegate& _eventDelegate, 
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
	// Search listeners for an existing event type
	auto findIt = eventListeners.find(_ptrEvent->VGetEventType());
	if (findIt != eventListeners.end())
	{
		// If we do not find it, add this event to the active queue
		queues[activeQueue].push_back(_ptrEvent);
		return true;
	}
	else
	{
		return false;
	}
}

bool EventManager::VTerminateAll(const EventType& _targetType)
{
	bool success = false;
	EventListenerMap::iterator findIt = eventListeners.find(_targetType);

	if (findIt != eventListeners.end())
	{
		EventQueue& eventQueue = queues[activeQueue];
		auto it = eventQueue.begin();
		while (it != eventQueue.end())
		{
			// Do not remove item using iterator itself
			auto thisIt = it;
			// If event here is target type, erase it from queue
			if ((*thisIt)->VGetEventType() == _targetType)
			{
				eventQueue.erase(thisIt);
				success = true;
			}
			// Increment and continue
			++it;
		}
	}
	return success;
}

void EventManager::VUpdate(unsigned long _maxMs)
{
	// unsigned long currMs = getTicks()
	// unsigned long maxMs = currMs + _maxMs

	// Swap active queues, clear new queue
	int queueToProcess = activeQueue;
	activeQueue = (activeQueue+1)%EM_NUMBER_OF_QUEUES;
	queues[activeQueue].clear();

	// Process the exisiting queue
	while (queues[queueToProcess].empty()==false)
	{
		// Grab next event and pop front of queue
		IEventDataPtr ptrEvent = queues[queueToProcess].front();
		queues[queueToProcess].pop_front();

		const EventType& eventType = ptrEvent->VGetEventType();

		// Find all delegates registered to this event
		auto findIt = eventListeners.find(eventType);
		if(findIt != eventListeners.end())
		{
			const EventListenerList& updateEventListeners = findIt->second;
			for (auto it = updateEventListeners.begin(); it != updateEventListeners.end();
				it++)
			{
				// Call each listeners delegate
				EventListenerDelegate listener = (*it);
				listener(ptrEvent);
			}
		}

		// Check to see if processing time is run out
		/* Not using this functionality at the moment
		currMs = getTicks();
		if (currMs > maxMs)
		{
			break;
		}
		*/
		
	}
}