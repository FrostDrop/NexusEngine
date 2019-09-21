#include "Nexus.h"
#include <iostream>


class Sandbox : public Nexus::Application
{

public:

	Sandbox()
	{
		std::cout << "Hello Nexus!" << std::endl;
	}

	~Sandbox()
	{
		std::cout << "Bye Nexus!" << std::endl;
	}

};

Nexus::Application* Nexus::CreateApplication()
{
	return new Sandbox();
}

