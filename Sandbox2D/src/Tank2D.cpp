#include <Reme.h>
#include <Core/EntryPoint.h>

class Tank2D : public Reme::Application
{
public:
	Tank2D() : Application("Tank2D", 640, 640)
	{
		float aspectRatio = 640.0f / 640.0f;
		cam = new Reme::OrthographicCamera(-aspectRatio, aspectRatio, 1.0f, -1.0f);
		imgs[0] = Reme::Texture::Create("assets/miku-cutie.jpg");
		imgs[1] = Reme::Texture::Create("assets/rem-bb.png");
		imgs[2] = Reme::Texture::Create("assets/rem-sleeping-rose.png");
		imgs[3] = Reme::Texture::Create("assets/you2.jpg");
		imgs[4] = Reme::Texture::Create("assets/you-waifu-material.jpg");
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

		float x = 0.0f;
		float y = 0.0f;
		for (int i = 0; i < imgs.size(); i++)
		{			
			DrawTexture(imgs[i], { 200.0f, y });
			y += 400.0f;
		}

		Reme::Renderer2D::End();
	}
private:
	Reme::OrthographicCamera* cam;
	std::array<Reme::Texture*, 5> imgs;
};

Reme::Application* Reme::CreateApplication()
{
	return new Tank2D();
}
