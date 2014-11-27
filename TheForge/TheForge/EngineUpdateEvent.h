#ifndef ENGINE_UPDATE_EVENT
#define ENGINE_UPDATE_EVENT

#include "Events\EventData.h"

class EngineUpdateEvent : public BaseEventData
{
public:
	EngineUpdateEvent(void);
	~EngineUpdateEvent(void);
};

#endif


