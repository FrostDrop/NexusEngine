#include "Nexus.h"
#include <iostream>


class FSandbox : public Nexus::FApplication
{

public:

	FSandbox()
	{
		std::cout << "Hello Nexus!" << std::endl;
	}

	~FSandbox()
	{
		std::cout << "Bye Nexus!" << std::endl;
	}

};

Nexus::FApplication* Nexus::CreateApplication()
{
	return new FSandbox();
}

