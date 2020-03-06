#include <Reme.h>
#include <Core/EntryPoint.h>

extern "C"
{
#include <lua/lua.h>
#include <lua/lauxlib.h>
#include <lua/lualib.h>
}

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

		lua_State *L = luaL_newstate();
		int r = luaL_dostring(L, "a = 7 + 12");
		if (r == LUA_OK)
		{
			lua_getglobal(L, "a");
			if (lua_isnumber(L, -1))
			{
				float a_in_cpp = (float) lua_tonumber(L, -1);
				LOG_INFO("a_in_cpp = {}", a_in_cpp);
			}
		}
		else
		{
			LOG_ERROR("LUA ERROR: {}", lua_tostring(L, -1));
		}

		lua_close(L);
	}

	~Tank2D()
	{

	}

	void OnUpdate(double deltaTime) override
	{
		float speed = 0.01;
		glm::vec3 v = { 0.0f, 0.0f, 0.0f };
		if (IsKeyPressed(Reme::KeyCode::W))
			v.y -= speed;
		if (IsKeyPressed(Reme::KeyCode::A))
			v.x -= speed;
		if (IsKeyPressed(Reme::KeyCode::S))
			v.y += speed;
		if (IsKeyPressed(Reme::KeyCode::D))
			v.x += speed;

		if (v.x != 0.0f || v.y != 0.0f || v.z != 0.0f)
		{
			cam->SetPosition(cam->GetPosition() + v);
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

	void OnResize(int width, int height) override
	{
		float ratio = (float) width / (float) height;
		cam->SetProjection(-ratio, ratio, 1.0f, -1.0f);
		LOG_INFO("Screen resized, new resolution: {}x{}", width, height);
	}
private:
	Reme::OrthographicCamera* cam;
	std::array<Reme::Texture*, 5> imgs;
};

Reme::Application* Reme::CreateApplication()
{
	return new Tank2D();
}
