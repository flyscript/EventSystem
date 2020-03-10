# EventSystem
A fast, comprehensive, and memory-efficient enum-based events system I created on the side during my Masters course

Inside [EventSystem/main.cpp](https://github.com/flyscript/EventSystem/blob/master/EventSystem/main.cpp) are a series of tests to demonstrate the system's capabilities. When the program is run, these are demonstrated.

### Key Features:
* Add [many listeners](https://github.com/flyscript/EventSystem/blob/master/EventSystem/main.cpp#L88) for an [event](https://github.com/flyscript/EventSystem/blob/master/EventSystem/EventManager.h#L65)
* Add [many events](https://github.com/flyscript/EventSystem/blob/master/EventSystem/main.cpp#L91) for a [listener](https://github.com/flyscript/EventSystem/blob/master/EventSystem/EventListener.h)
* [Remove all](https://github.com/flyscript/EventSystem/blob/master/EventSystem/EventManager.cpp#L110) listener-event connections for an event
* [Remove specified listener-event](https://github.com/flyscript/EventSystem/blob/master/EventSystem/EventManager.cpp#L89) connections for an event
* Run faster than string-based systems; due to simple numerical comparisons rather than strings, and a robust [enum-sequenced](https://github.com/flyscript/EventSystem/blob/master/EventSystem/EventListener.h#L22) event address tabling system
* [Pass data](https://github.com/flyscript/EventSystem/blob/master/EventSystem/main.cpp#L122) through event triggers and [callbacks](https://github.com/flyscript/EventSystem/blob/master/EventSystem/EventListener.cpp#L45)
