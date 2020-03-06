#include <Reme.h>
#include <Core/EntryPoint.h>

class Tank2D : public Reme::Application
{
public:
	Tank2D() : Application("Tank2D", 640, 640)
	{
		float aspectRatio = 640.0f / 640.0f;
		cam = new Reme::OrthographicCamera(-aspectRatio, aspectRatio, 1.0f, -1.0f);
		img = Reme::Texture::Create("you-waifu-material.jpg");
	}

	~Tank2D()
	{

	}

	void OnUpdate(double deltaTime) override
	{
		float speed = 0.01;
		if (IsKeyPressed(Reme::KeyCode::W))
		{
			cam->Position.y -= speed;
			cam->ReCalc();
		}

		if (IsKeyPressed(Reme::KeyCode::A))
		{
			cam->Position.x -= speed;
			cam->ReCalc();
		}

		if (IsKeyPressed(Reme::KeyCode::S))
		{
			cam->Position.y += speed;
			cam->ReCalc();
		}

		if (IsKeyPressed(Reme::KeyCode::D))
		{
			cam->Position.x += speed;
			cam->ReCalc();
		}
	}

	void OnRender() override
	{
		Reme::Renderer2D::Begin(cam);
		DrawRect({ 1.0f, 0.0f, 0.0f, 1.0f }, { 320.0f, 240.0f }, { 200.0f, 200.0f });
		DrawTexture(nullptr, { 100.0f, 100.0f });
		DrawTexture(img, { 0.0f, 0.0f });
		Reme::Renderer2D::End();
	}
private:
	Reme::OrthographicCamera* cam;
	Reme::Texture* img;
};

Reme::Application* Reme::CreateApplication()
{
	return new Tank2D();
}
