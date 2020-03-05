#include <Reme.h>
#include <Core/EntryPoint.h>

class Tank2D : public Reme::Application
{
public:
	Tank2D()
	{

	}

	~Tank2D()
	{

	}

	void OnRender() override
	{
		DrawRect({ 1.0f, 0.0f, 0.0f, 1.0f }, { 0.0f, 0.0f }, { 200.0f, 200.0f });
	}
};

Reme::Application* Reme::CreateApplication()
{
	return new Tank2D();
}
