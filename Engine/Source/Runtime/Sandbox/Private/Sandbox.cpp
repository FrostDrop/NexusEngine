#include <iostream>

#include "Core.h"
#include "HAL/Memory.h"
#include "HAL/MallocAnsi.h"
#include "Containers/Array.h"

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
			TArray<uint32> Array;

			Array.Add(1);
			Array.Add(2);

			Array.Insert(3, 1);

			for (uint32 i = 0; i < Array.Num(); ++i)
				Array.RemoveAt(0);

			for (uint32 i = 0; i < Array.Num(); ++i)
				std::cout << Array[i] << std::endl;


			std::vector<uint32> Vector;
			Vector.push_back(1);
			Vector.push_back(2);

			Vector.insert(Vector.begin() + 1, 3);
			
			for (uint32 i = 0; i < Vector.size(); ++i)
				Vector.erase(Vector.begin());

			for (uint32 i = 0; i < Vector.size(); ++i)
				std::cout << Vector[i] << std::endl;
		}

	};

	FApplication* CreateApplication()
	{
		return new FSandbox();
	}

}


