#include <iostream>

#include "Core.h"
#include "HAL/Memory.h"
#include "HAL/MallocAnsi.h"
#include "Containers/Array.h"
#include "Containers/BitArray.h"

#include <vector>

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
			TBitArray Other = TBitArray(true, 32);
			TBitArray BitArray = MoveTemp(Other);

			BitArray.Add(false);
			BitArray.Add(true);
			BitArray.Add(false);

			std::cout << BitArray.FindLast(false) << std::endl;
		}

	};

	FApplication* CreateApplication()
	{
		return new FSandbox();
	}

}


