#pragma once

#include "Core/Log.h"
#include "Core/Application.h"

extern Reme::Application* Reme::CreateApplication();

int main()
{
	Reme::Log::Init();
	auto app = Reme::CreateApplication();
	app->Run();
	delete app;
}
