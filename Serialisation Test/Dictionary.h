#pragma once
#include "RDSerialisation.h"
class dictionary
{
public:
	~dictionary() { } // public destructor
	
	template<class Data>
	Data getData();
private:
	dictionary() { }
	static dictionary* instance;
}; 
dictionary* dictionary::instance = nullptr;

template<class Data>
Data dictionary::getData()
{
	if (!Serialisor::getInstance()->openFile("Test.RDV"))
		return NULL;

}