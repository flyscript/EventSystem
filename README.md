# EventSystem
A fast, comprehensive, and memory-efficient enum-based events system I created on the side during my Masters course
\n
Inside EventSystem/main.cpp are a series of tests to demonstrate the system's capabilities. When the program is run, these are demonstrated.
\n
This system has the ability to:
*Add many listeners for an event
*Add many events for a listener
*Remove all listener-event connections for an event
*Remove specified listener-event connections for an event
*Run faster than string-based systems; due to simple numerical comparisons rather than strings, and a robust enum-sequenced event address tabling system
