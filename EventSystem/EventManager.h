/*

	EventManager.h
	Will Chapman
	07/11/2019

	This header file describes the architecture of the EventManager class.


	> To add more event types, see EventListener.h


	> To add a listener for an event, simply call:

		AddListener(EventType, std::function<void()>) 
	
		with the event it's for, and a pointer to the function that will be called
		when that event occurs. That function should receive a void* as its only 
		argument so that it can be passed data by triggers. As this isn't-type safe,
		ensure you cast or check appropriately. You might want to use a struct.


	> To trigger an event, simply call:

		Trigger(EventType, void*);

		with the type of event that's being triggered, and a pointer to any relevant
		data that your listeners may need. As this isn't type-safe, listeners should
		ensure they cast or check it appropriately. You might want to use a struct.
*/

#ifndef EVENT_MANAGER_H
#define EVENT_MANAGER_H


// Includes
#include "EventListener.h"
#include <functional>
#include <vector>


/*
	Event Manager
	----------
	This class manages the trigger requests, and subsequent triggering, of events.

	Anything can trigger an event, and anything can listen for events.

	Each event type, as listed in the enum EventType in EventListener.h, gets its
	own list created when the manager is initialized. When an event is triggered,
	the manager will go through the appropriate list and send a trigger to each
	listener.

	This way, no expensive string comparisons need to take place, and you don't need
	a memory-expensive VTable or map of listeners to save the other expensive case of
	every listener hearing every event and having to do its own check on whether it's
	theirs or not, or do any complex sort or search algorithms.

*/
class EventManager
{
private:
	
	// This array will hold an array of event listeners, sorted by EventType
	std::vector<std::vector<EventListener*>>* m_aListOfEventListenerLists;
	
protected:

	//Constructor
	EventManager();

	// Destructor
	~EventManager();

public:

	// Singleton
	static EventManager& Manager();

	// Delete copy, move, and assign
	EventManager( EventManager const& ) = delete;             // Copy construct
	EventManager( EventManager&& ) = delete;                  // Move construct
	EventManager& operator=( EventManager const& ) = delete;  // Copy assign
	EventManager& operator=( EventManager && ) = delete;      // Move assign

	// Adds a listener for a given event, returns the eventlistener in question
	EventListener* AddListener( EventType eEventType, std::function<void( void* )> pfnCallback );
	EventListener* AddListener( EventType eEventType, EventListener* pListener );

	// Removes listener for a given event
	void RemoveListener( EventType eEventType, EventListener* pListener );

	// Removes listeners for all events
	void RemoveAllListeners( EventType eEventType );

	// Triggers events of given type
	void Trigger(EventType eEventType, void* data);
};

#endif
