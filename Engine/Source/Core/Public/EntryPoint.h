#pragma once

#include "Application.h"

namespace Nexus
{

	extern FApplication* CreateApplication();

}


int main(int argc, char** argv)
{
	Nexus::FApplication* app = Nexus::CreateApplication();
	app->Run();
	delete app;
}
