#define REME_ENTRY_POINT
#include <Reme.h>

#include "Test.h"
#include "Tank2D/Tank2D.h"

class Game : public Reme::Application
{
public:
	Game()
	{
		GetScreen().PushLayer(new Test());
		// GetScreen().PushLayer(new Tank2D());
	}
};

Reme::Application* Reme::CreateApplication()
{
	return new Game();
}
