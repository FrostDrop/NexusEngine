#include "Nexus.h"
#include <iostream>


class FSandbox : public Nexus::FApplication
{

public:

	FSandbox()
	{
		std::cout << "Hello Nexus!" << std::endl;
	}

	virtual ~FSandbox()
	{
		std::cout << "Bye Nexus!" << std::endl;
	}

	virtual void Run() override
	{

	}

};

Nexus::FApplication* Nexus::CreateApplication()
{
	return new FSandbox();
}

