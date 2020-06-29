#include <iostream>

#include "Core.h"
#include "HAL/Memory.h"
#include "HAL/MallocAnsi.h"
#include "Containers/Array.h"
#include "Containers/BitArray.h"

#include "Math/Matrix.h"


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
			TArray<FMatrix> MatrixArray;

			FMatrix Matrix = FMatrix(
				FVector(2.0f, 0.0f, 0.0f),
				FVector(0.0f, 4.0f, 0.0f),
				FVector(0.0f, 0.0f, 3.0f),
				FVector(0.0f, 0.0f, 0.0f)
			);

			MatrixArray.Add(Matrix.GetInverse());
		}

	};

	FApplication* CreateApplication()
	{
		return new FSandbox();
	}

}


