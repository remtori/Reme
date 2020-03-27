#define REME_ENTRY_POINT
#include <Reme.h>

#include "Test.h"

class Game : public Reme::Application
{
public:
	Game()
	{
		GetScreen().PushLayer(new Test());
	}
};

Reme::Application* Reme::CreateApplication()
{
	return new Game();
}
