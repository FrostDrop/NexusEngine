#include <iostream>

#include "Core.h"

namespace Nexus
{

	class FSandbox : public FApplication
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

	FApplication* CreateApplication()
	{
		return new FSandbox();
	}

}


