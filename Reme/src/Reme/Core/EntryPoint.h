#ifdef REME_ENTRY_POINT

#include "Reme/Core/Log.h"
#include "Reme/Core/Application.h"
#include "Reme/Debug/Instrumentor.h"

extern Reme::Application* Reme::CreateApplication();

int main(int argc, char** argv)
{
	Reme::Log::Init();
	
	PROFILE_BEGIN_SESSION("Startup", "RemeProfile-Startup.json");
	auto app = Reme::CreateApplication();
	PROFILE_END_SESSION();

	PROFILE_BEGIN_SESSION("Runtime", "RemeProfile-Runtime.json");
	app->Run();
	PROFILE_END_SESSION();

	PROFILE_BEGIN_SESSION("Startup", "RemeProfile-Shutdown.json");
	delete app;
	PROFILE_END_SESSION();
}
#endif
