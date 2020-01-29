/*

	EventListener.h
	Will Chapman
	07/11/2019

	This header file describes the architecture of the EventListener class, as well
	as the enumerable event types.


*/

#ifndef EVENT_LISTENER_H
#define EVENT_LISTENER_H



// Includes
#include <functional>

/*
Event Type
----------
An enum containing events that can be triggered.

Add any events you want, just ensure iterator_end remains the last one.
*/
enum EventType
{
	EventA = 0,
	EventC,
	EventD,
	EventB,
	EventE,
	iterator_end
};

/*
	EventListener
	-------------
	A class used by EventManager to map trigger requests to the firing of the relevant events

	Could have just been a function pointer, but this allows for any potential future expandability
*/
class EventListener
{
private:

	// Pointer to the function that'll be called when this event is triggered
	std::function<void(void*)> m_pfnCallback;

	// The kind of event that this listener is for
	EventType m_eEventType;

public:

	// Default constructor
	EventListener();

	// A constructor that sets the callback and event type
	EventListener(std::function<void(void*)> pfnCallback, EventType eEventType);

	// Destructor
	~EventListener();

	// Runs the callback
	void Trigger(void* data);


	///////////////////////////////////
	//	Setters and Getters
	///////////////////////////////////

	// Setter for event type
	inline void SetEventType(EventType eEventType)
	{
		// Only set if not already set
		if (!m_eEventType)
		{
			m_eEventType = eEventType;
		}
	}

	// Getter for event type
	inline EventType GetEventType()
	{
		return m_eEventType;
	}

	// Setter for callback
	inline void SetCallback(std::function<void(void*)> pfnCallback)
	{
		m_pfnCallback = pfnCallback;
	}

	// Getter for callback
	inline std::function<void(void*)> GetCallback()
	{
		return m_pfnCallback;
	}

};

#endif