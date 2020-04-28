#include <iostream>

#include "Core.h"
#include "HAL/Memory.h"
#include "HAL/MallocAnsi.h"

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
			void* Memory = FMemory::Malloc(1000);

			FMemory::Free(Memory);
		}

	};

	FApplication* CreateApplication()
	{
		return new FSandbox();
	}

}


