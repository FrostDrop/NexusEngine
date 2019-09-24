#pragma once

#include "Application.h"

namespace Nexus
{

	extern Application* CreateApplication();

}


int main(int argc, char** argv)
{
	Nexus::Application* app = Nexus::CreateApplication();
	app->Run();
	delete app;
}
