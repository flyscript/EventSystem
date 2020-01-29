/*

	main.cpp
	Will Chapman
	07/11/2019

	This .cpp file demonstrates the abilities of my event manager system.
	
	See EventManager.h for further information on how this works.

	This file demonstrates how it can be used.

	Below, you will see that:
	
		> there can be many listeners for one event
			(EventA > callbackForA1 and EventA > callbackForA2)

		> you can have more than one event trigger
			result in the the same callback being fired
			(EventA > callbackForA2 and EventB > callbackForA2)

		> you can pass data through events
			(EventC > callbackForC)

*/
//Includes
#include "EventManager.h"
#include <iostream>


///////////////////////////////////
//	Event Functions
///////////////////////////////////

// Example struct types for passing some data
struct tempStruct1
{
	int myNumber = 5;
};

struct tempStruct2
{
	int myNumber = 5;
	bool myBool = true;
};

void callbackForA1(void* pData )
{
	std::cout << "Callback A1 happened!" << std::endl;
}

void callbackForA2(void* pData )
{
	std::cout << "Callback A2 happened!" << std::endl;
}

void callbackForC(void* pData )
{
	std::cout << "Callback C happened!" << std::endl;

	std::cout << "Event C's raw argument was : '" << pData << "'" << std::endl;

	tempStruct2* converted = static_cast<tempStruct2*>( pData );
	if (converted)
	{
		char msg[50];
		sprintf_s(msg, "Converted view of Event C's argument: %d, %d", converted->myNumber, converted->myBool );
		std::cout << msg << std::endl;
	}
}

////////////////////////////////////////////////////////////////



///////////////////////////////////
//	Main
///////////////////////////////////

int main(std::string args[])
{
	std::cout << "Running event system test..." << std::endl << std::endl;

	//Create the event manager
	EventManager& eventManager = EventManager::Manager();


	// Create listeners. One event can have many listeners.
	std::cout << "Adding event listeners..." << std::endl;	
	eventManager.AddListener( EventA, callbackForA1 );
	auto removable = eventManager.AddListener( EventA, callbackForA2 );
	eventManager.AddListener( EventB, callbackForA2 );
	eventManager.AddListener( EventC, callbackForC );

	// A listener can also be a lambda
	eventManager.AddListener( 
		EventE, [&] ( void* pData )
		{
		std::cout << "Lambda Callback happened!" << std::endl;

		std::cout << "Lambda / Event E's raw argument was : '" << pData << "'" << std::endl;

		tempStruct1* converted = static_cast< tempStruct1* >( pData );
		if ( converted )
		{
			char msg[50];
			sprintf_s( msg, "Converted view of Lambda/Event E's arguments: %d", converted->myNumber );
			std::cout << msg << std::endl;
		}
		}		
	);


	// Event A has two listeners for it, A1 and A2
	std::cout << std::endl << std::endl << "Triggering event listeners for EventA..." << std::endl << std::endl;
	eventManager.Trigger(EventA, nullptr);

	// Event B has one listener for it, which is A2
	std::cout << std::endl << std::endl << "Triggering event listeners for EventB..." << std::endl << std::endl;
	eventManager.Trigger(EventB, nullptr);

	// Event C demonstrates the ability to pass data through events
	tempStruct2 myStruct2;
	myStruct2.myNumber = 69;
	myStruct2.myBool = false;
	std::cout << std::endl << std::endl << "Triggering event listeners for EventC with data " << myStruct2.myNumber << " | " << myStruct2.myBool << " @ 0x" << &myStruct2 << "..." << std::endl << std::endl;
	eventManager.Trigger(EventC, &myStruct2);
	
	// Event D demonstrates what happens if you trigger an event with no listeners (hint: it's nothing)
	std::cout << std::endl << std::endl << "Triggering event listeners for EventD..." << std::endl << std::endl;

	// Event E demonstrates how a lambda listener works
	tempStruct1 myStruct1;
	myStruct1.myNumber = 420;
	std::cout << std::endl << std::endl << "Triggering event listeners for EventE with data " << myStruct1.myNumber <<" @ 0x" << &myStruct2 << "..." << std::endl << std::endl;
	eventManager.Trigger( EventE, &myStruct1 );
	
	// Now we'll delete one of event A's listeners to show how that's done
	/*
		One caveat of this implementation is that you have to supply the event type AND listener
		you want to remove, but that's very much worth it for the performance, and ensures you're
		deleting the right thing
	*/
	std::cout << std::endl << std::endl << "Removing one event listener for EventA..." << std::endl << std::endl;
	eventManager.RemoveListener( EventA, removable );

	std::cout << std::endl << std::endl << "Triggering event listeners for EventA..." << std::endl << std::endl;
	eventManager.Trigger( EventA, nullptr );

	// Now we'll delete all event As
	std::cout << std::endl << std::endl << "Removing all event listeners for EventA..." << std::endl << std::endl;
	eventManager.RemoveAllListeners( EventA );

	// Now we'll see what happens when we trigger event A now that all the listeners are gone (hint: it's also nothing)
	std::cout << std::endl << std::endl << "Triggering event listeners for EventA..." << std::endl << std::endl;
	eventManager.Trigger( EventA, nullptr );

	//Exit
	std::cout << std::endl << std::endl << "Complete!" << std::endl << std::endl << "Press Any Key To Exit" << std::endl << std::endl;

	std::cin.get();
}