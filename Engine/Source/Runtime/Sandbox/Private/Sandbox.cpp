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
			TBitArray BitArray = TBitArray(1, 32);

			BitArray.Add(true);
			BitArray.Add(false);

			BitArray.SetRange(0, 2, true);
			BitArray.RemoveAt(0);

			std::cout << BitArray[0] << std::endl;
		}

	};

	FApplication* CreateApplication()
	{
		return new FSandbox();
	}

}


