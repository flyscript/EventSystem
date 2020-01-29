/*

	EventManager.cpp
	Will Chapman
	07/11/2019

	This header file defines the functionality of the EventManager class


*/

// Include .h
#include "EventManager.h"
#include <iostream>



// Singleton behaviour
EventManager& EventManager::Manager()
{
	static EventManager cInstance;

	return cInstance;
}


// Constructor
EventManager::EventManager()
{
	// Initialize list of event listener lists
	m_aListOfEventListenerLists = new std::vector<std::vector<EventListener*>>();

	// Add in a list for each event type
	for (int fooInt = 0; fooInt != iterator_end; fooInt++)
	{
		// Create new vector of event listeners
		std::vector<EventListener*>* aNewListOfListeners = new std::vector<EventListener*>();

		// Add it to the list of event listener lists
		m_aListOfEventListenerLists->push_back(*aNewListOfListeners);
	}
}


// Destructor
EventManager::~EventManager()
{
	// Vectors delete all their contents so this is as much as needs to be managed
	delete m_aListOfEventListenerLists;
}


// Adds a listener to the appropriate list via an explicit listener
EventListener* EventManager::AddListener( EventType eEventType, EventListener* pListener )
{
	// Get the relevant index in the list of event types
	int iIndex = static_cast< int >( eEventType );

	// Get the relevant list with that index
	std::vector<EventListener*>* listOfListeners = &m_aListOfEventListenerLists->at( iIndex );

	// Add the new listener into that list
	listOfListeners->push_back( pListener );

	//Return the listener
	return pListener;
}

// Adds a listener to the appropriate list via a callback function - returns the listener it makes
EventListener* EventManager::AddListener( EventType eEventType, std::function<void( void* )> pfnCallback )
{
	// Get the relevant index in the list of event types
	int iIndex = static_cast< int >( eEventType );

	// Get the relevant list with that index
	std::vector<EventListener*>* listOfListeners = &m_aListOfEventListenerLists->at( iIndex );

	// Create new event listener
	EventListener* aNewListener = new EventListener( pfnCallback , eEventType );

	// Add the new listener into that list
	listOfListeners->push_back( aNewListener );

	//Return the listener
	return aNewListener;
}

// Simple brute-force remove
void EventManager::RemoveListener( EventType eEventType, EventListener* pListener )
{
	// Get the relevant index in the list of event types
	int iIndex = static_cast< int >( eEventType );

	// Get the relevant list with that index
	std::vector<EventListener*>* listOfListeners = &m_aListOfEventListenerLists->at( iIndex );
	
	// Search that list
	for ( unsigned i = 0; i < listOfListeners->size(); i++ )
	{
		// Delete the listener
		if ( listOfListeners->at( i ) == pListener )
		{
			listOfListeners->erase( listOfListeners->begin() + i );
			break;
		}
	}
}

// Removes all events of a certain type
void EventManager::RemoveAllListeners( EventType eEventType )
{
	// Get the relevant index in the list of event types
	int iIndex = static_cast< int >( eEventType );

	// Get the relevant list with that index
	std::vector<EventListener*>* listOfListeners = &m_aListOfEventListenerLists->at( iIndex );

	// Delete contents of the array of listeners
	listOfListeners->clear();
}

// Tells event manager to trigger events of a given type
void EventManager::Trigger(EventType eEventType, void* pData)
{
	// Get the relevant index in the list of event types
	int iIndex = static_cast<int>(eEventType);

	// Get list of listeners to trigger
	std::vector<EventListener*>* aListOfListeners = &m_aListOfEventListenerLists->at(iIndex);

	// Trigger all listeners for that event
	for each ( auto eventListener in *aListOfListeners)
	{
		eventListener->Trigger( pData );
	}
}