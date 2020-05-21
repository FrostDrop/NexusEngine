#include <iostream>

#include "Core.h"
#include "HAL/Memory.h"
#include "HAL/MallocAnsi.h"
#include "Containers/Array.h"
#include "Containers/BitArray.h"
#include "Containers/String.h"


namespace Nexus
{

	class FSandbox : public FApplication
	{

	public:

		FSandbox()
		{
			std::cout << "Hello Nexus!" << std::endl;
			GMalloc = new FMallocAnsi;
		}

		virtual ~FSandbox()
		{
			std::cout << "Bye Nexus!" << std::endl;
		}

		virtual void Run() override
		{
			FString Message = FString(11, "Nexus Message");

			std::cout << *Message << std::endl;
			std::cout << Message[0] << std::endl;

		}

	};

	FApplication* CreateApplication()
	{
		return new FSandbox();
	}

}


