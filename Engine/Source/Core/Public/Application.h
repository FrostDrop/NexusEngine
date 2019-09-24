#pragma once

#include "Platform/Platform.h"


namespace Nexus
{

	class NEXUS_API Application
	{

	public:

		Application();
		virtual ~Application();

		void Run();

		NEXUS_INLINE Application* GetInstance() { return Instance; }

	private:

		static Application* Instance;

	};

}