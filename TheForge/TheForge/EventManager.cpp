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

}
	
bool EventManager::VTriggerEvent(const IEventDataPtr& _ptrEvent)
{

}
	
bool EventManager::VQueueEvent(const IEventDataPtr& _ptrEvent)
{

}

bool EventManager::VTerminateAll(const EventType& _type)
{

}

void EventManager::VUpdate(unsigned long _maxMilliseconds = 9999)
{

}