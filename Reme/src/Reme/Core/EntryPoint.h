#pragma once

#include "Reme/Core/Log.h"
#include "Reme/Core/Application.h"

extern Reme::Application* Reme::CreateApplication();

int main()
{
	Reme::Log::Init();
	auto app = Reme::CreateApplication();
	app->Run();
	delete app;
}
