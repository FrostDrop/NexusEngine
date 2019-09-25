#pragma once

#include "Platform/Platform.h"


namespace Nexus
{

	class NEXUS_API FApplication
	{

	public:

		FApplication();
		virtual ~FApplication();

		void Run();

		NEXUS_INLINE FApplication* GetInstance() { return Instance; }

	private:

		static FApplication* Instance;

	};

}