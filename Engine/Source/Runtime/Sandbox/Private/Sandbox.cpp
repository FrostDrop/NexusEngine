#include <iostream>

#include "Core.h"
#include "HAL/Memory.h"
#include "HAL/MallocAnsi.h"
#include "Containers/Array.h"

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
			TArray<uint32> Array;

			Array.Add(1);
			Array.Add(2);

			Array.Insert(3, 1);

			TArray<uint32> Other = Array;
			Other.Add(4);
			Other.Insert(5, 0);

			Array = Other;

			Array += Other;
			Array += { 1, 2, 3, 4, 5 };

			for (uint32 i = 0; i < Array.Num(); ++i)
				std::cout << Array[i] << std::endl;
		}

	};

	FApplication* CreateApplication()
	{
		return new FSandbox();
	}

}


