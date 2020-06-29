#include <iostream>

#include "Core.h"
#include "Math/Matrix.h"

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
			FMatrix Matrix = FMatrix(
				FVector(3.0f, 0.0f, 0.0f),
				FVector(0.0f, 4.0f, 0.0f),
				FVector(0.0f, 0.0f, 2.0f),
				FVector(0.0f, 0.0f, 0.0f)
			);

			FMatrix Other = FMatrix(
				FVector(3.0f, 0.0f, 0.0f),
				FVector(0.0f, 4.0f, 0.0f),
				FVector(0.0f, 0.0f, 2.0f),
				FVector(0.0f, 0.0f, 0.0f)
			);

			FMatrix Inverse = Matrix.GetInverse() * Matrix * 2.5f;

			std::cout << Inverse.M[0][0] << " " << Inverse.M[0][1] << " " << Inverse.M[0][2] << " " << Inverse.M[0][3] << std::endl;
			std::cout << Inverse.M[1][0] << " " << Inverse.M[1][1] << " " << Inverse.M[1][2] << " " << Inverse.M[1][3] << std::endl;
			std::cout << Inverse.M[2][0] << " " << Inverse.M[2][1] << " " << Inverse.M[2][2] << " " << Inverse.M[2][3] << std::endl;
			std::cout << Inverse.M[3][0] << " " << Inverse.M[3][1] << " " << Inverse.M[3][2] << " " << Inverse.M[3][3] << std::endl;
		}

	};

	FApplication* CreateApplication()
	{
		return new FSandbox();
	}

}


