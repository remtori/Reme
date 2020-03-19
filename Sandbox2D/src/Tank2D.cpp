#include <Reme.h>
#include <Core/EntryPoint.h>
#include <imgui/imgui.h>

extern "C"
{
#include <lua/lua.h>
#include <lua/lauxlib.h>
#include <lua/lualib.h>
}

#include <fstream>
#include <numeric>
#include <algorithm>

class Tank2D : public Reme::Application
{
public:
	Tank2D() : Application("Tank2D", 640, 640)
	{
		cam = new Reme::OrthographicCamera(0.0f, 640.f, 640.0f, 0.0f);
		imgs[0] = Reme::Texture::Create("assets/miku-cutie.jpg");
		imgs[1] = Reme::Texture::Create("assets/rem-bb.png");
		imgs[2] = Reme::Texture::Create("assets/rem-sleeping-rose.png");
		imgs[3] = Reme::Texture::Create("assets/you-waifu-material.jpg");
		avgFps.fill(0.0f);
		benchmarkName.fill('\0');

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

	void OnUpdate(double ellapsedTime) override
	{
		float speed = 300 * ellapsedTime;
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

		float y = 0.0f;
		do {
			for (int i = 0; i < imgs.size(); i++)
			{
				float ratio = (float)imgs[i]->GetWidth() / (float)imgs[i]->GetHeight();
				float dHeight = imgWidth / ratio;

				for (int j = 0; j < m_WinInfo.Width / imgWidth; j++)
				{
					DrawTexture(imgs[i], { imgWidth * j, y }, { imgWidth, dHeight });
				}

				y += dHeight;
			}
		} while (y < m_WinInfo.Height);

		for (float x = 0.0f; x < m_WinInfo.Width; x += rectSize)
		{
			for (float y = 0.0f; y < m_WinInfo.Height; y += rectSize)
			{
				DrawRect(
					{ 
						static_cast<uint8_t>((x / m_WinInfo.Width) * 255), 
						static_cast<uint8_t>((y / m_WinInfo.Height) * 255),
						255, 
						255 
					}, 
					{ x, y }, 
					{ rectSize - 4.0f, rectSize - 4.0f }
				);
			}
		}

		DrawRect(Reme::Color::Red, { 100.0f, 0.0f }, { 50.0f, 50.0f });
		DrawTexture(nullptr, { 100.0f, 100.0f });

		Reme::Renderer2D::End();
	}

	void OnImGuiRender() override
	{
		ImGui::Begin("Menu");
		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
		ImGui::DragFloat("Img Width", &imgWidth, 1.0f, 1.0f, 1000.0f);
		ImGui::DragFloat("Rect Size", &rectSize, 1.0f, 5.0f, 1000.0f);

		ImGui::InputText("Benchmark name", benchmarkName.data(), sizeof(benchmarkName));
		if (ImGui::Button("Start Benchmark"))
		{
			benchMarkStarted = true;
			avgFps.fill(0.0f);

			if (!std::equal(benchmarkName.begin(), benchmarkName.end(), createdFileName.begin()))
			{
				if (fOut.is_open()) fOut.close();
				fOut = std::ofstream(benchmarkName.data(), std::ios::out);
				std::copy(benchmarkName.begin(), benchmarkName.end(), createdFileName.begin());
			}
		}

		if (benchMarkStarted)
		{
			ImGui::Text("Benchmarking ...");
			std::rotate(avgFps.begin(), avgFps.begin() + 1, avgFps.end());
			avgFps[avgFps.size() - 1] = ImGui::GetIO().Framerate;			

			if (avgFps[0] > 0.0f)
			{
				auto mmFps = std::minmax_element(avgFps.begin(), avgFps.end());
				fOut << "Testing with:" << std::endl
					<< "\tScreen res: " << m_WinInfo.Width << "x" << m_WinInfo.Height << std::endl
					<< "\tImg Width: " << imgWidth << std::endl
					<< "\tRect Size: " << rectSize << std::endl
					<< "FPS: " << std::endl
					<< "\tMIN: " << *mmFps.first << std::endl
					<< "\tAVG: " << std::accumulate(avgFps.begin(), avgFps.end(), 0.0f) / (float)avgFps.size() << std::endl
					<< "\tMAX: " << *mmFps.second << std::endl;
				benchMarkStarted = false;
			}
		}

		ImGui::PlotHistogram("FPS", avgFps.data(), avgFps.size(), 0, nullptr, 0.0f, 400.0f, ImVec2(0.0f, 250.0f));

		ImGui::End();
	}

	void OnResize(int width, int height) override
	{
		cam->SetProjection(0.0f, width, height, 0.0f);		
		LOG_INFO("Screen resized, new resolution: {}x{}", width, height);
	}
private:
	std::ofstream fOut;
	std::array<char, 100> benchmarkName;
	std::array<char, 100> createdFileName;
	bool benchMarkStarted = false;
	float imgWidth = 50.0f;
	float rectSize = 50.0f;
	Reme::OrthographicCamera* cam;
	std::array<Reme::Texture*, 4> imgs;
	std::array<float, 250> avgFps;
};

Reme::Application* Reme::CreateApplication()
{
	return new Tank2D();
}
