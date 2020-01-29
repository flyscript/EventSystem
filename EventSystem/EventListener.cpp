/*

	EventListener.cpp
	Will Chapman
	07/11/2019

	This header file defines the very basic functionality of the EventListener class


*/


// Include .h
#include "EventListener.h"


// Constructor
EventListener::EventListener()
{

}


// Constructor with default values
EventListener::EventListener(std::function<void(void*)> pfnCallback, EventType eEventType)
	: m_pfnCallback(pfnCallback)
	, m_eEventType(eEventType)
{

}


// Destructor
EventListener::~EventListener()
{

}


// Triggers an individual listener's callback
void EventListener::Trigger(void* data)
{
	if (m_pfnCallback)
	{
		m_pfnCallback(data);
	}
}

