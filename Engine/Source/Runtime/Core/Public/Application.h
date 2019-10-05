#pragma once

#include "HAL/Platform.h"


namespace Nexus
{

	class CORE_API FApplication
	{

	public:

		FApplication();
		virtual ~FApplication();

		virtual void Run();

		FORCEINLINE FApplication* GetInstance() { return Instance; }

	private:

		static FApplication* Instance;

	};

}