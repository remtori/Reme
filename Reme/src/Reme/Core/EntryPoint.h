#ifdef REME_ENTRY_POINT

#include "Reme/Core/Log.h"
#include "Reme/Core/Application.h"

extern Reme::Application* Reme::CreateApplication();

int main(int argc, char** argv)
{
	Reme::Log::Init();
	auto app = Reme::CreateApplication();
	app->Run();
	delete app;
}
#endif
