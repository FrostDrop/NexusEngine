#include <iostream>

#include "Core.h"
#include "HAL/Memory.h"
#include "HAL/MallocAnsi.h"
#include "Containers/Array.h"
#include "Containers/BitArray.h"
#include "Containers/String.h"

#include "Misc/Char.h"

#include <iostream>
#include <string>
#include <locale>
#include <codecvt>

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
			FString Result = FString<AnsiChar>::Printf("%d %s", 5, "examples!");
			std::cout << *Result << std::endl;
		}

	};

	FApplication* CreateApplication()
	{
		return new FSandbox();
	}

}


