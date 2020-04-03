#pragma once

#include <Reme.h>

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

class Test : public Reme::Layer
{
public:
	void OnAttach() override
	{
		m_LayerName = "Tank2D";
		Reme::Application::Get().GetWindow().SetVSync(false);
		auto Width = Reme::Application::Get().GetWindow().GetWidth();
		auto Height = Reme::Application::Get().GetWindow().GetHeight();

		cam = Reme::CreateRef<Reme::OrthographicCamera>(0.0f, Width, Height, 0.0f);
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

	void OnDetach() override
	{

	}

	void OnUpdate(float elapsedTime) override
	{
		float speed = 300 * elapsedTime;
		glm::vec3 v = { 0.0f, 0.0f, 0.0f };
		if (Reme::Input::IsKeyPressed(Reme::KeyCode::W))
			v.y -= speed;
		if (Reme::Input::IsKeyPressed(Reme::KeyCode::A))
			v.x -= speed;
		if (Reme::Input::IsKeyPressed(Reme::KeyCode::S))
			v.y += speed;
		if (Reme::Input::IsKeyPressed(Reme::KeyCode::D))
			v.x += speed;

		if (v.x != 0.0f || v.y != 0.0f || v.z != 0.0f)
		{
			cam->SetPosition(cam->GetPosition() + v);
		}
	}

	void OnRender() override
	{
		auto Width = Reme::Application::Get().GetWindow().GetWidth();
		auto Height = Reme::Application::Get().GetWindow().GetHeight();

		Reme::Renderer2D::Begin(cam);

		float y = 0.0f;
		do {
			for (int i = 0; i < imgs.size(); i++)
			{
				float ratio = (float)imgs[i]->GetWidth() / (float)imgs[i]->GetHeight();
				float dHeight = imgWidth / ratio;

				for (int j = 0; j < Width / imgWidth; j++)
				{
					Reme::Renderer2D::DrawTexture(imgs[i], imgWidth * j, y, imgWidth, dHeight);
				}

				y += dHeight;
			}
		} while (y < Height);

		for (int x = 0.0f; x < Width; x += rectSize)
		{
			for (int y = 0.0f; y < Height; y += rectSize)
			{
				Reme::Renderer2D::DrawRect(
					Reme::Color(x % 255, y % 255, 255),
					x, y,
					rectSize - 2.0f, rectSize - 2.0f
				);
			}
		}

		Reme::Renderer2D::DrawRect(Reme::Color::Green,   0.0f, 100.0f, 50.0f, 50.0f);
		Reme::Renderer2D::DrawRect(Reme::Color::Red  , 100.0f, 100.0f, 50.0f, 50.0f);
		Reme::Renderer2D::DrawRect(Reme::Color::Blue , 100.0f,   0.0f, 50.0f, 50.0f);

		Reme::Renderer2D::PushState();
		Reme::Renderer2D::Translate(200.0f, 200.0f);
		Reme::Renderer2D::Rotate(glm::radians(rot));
		Reme::Renderer2D::Translate(-200.0f, -200.0f);
		Reme::Renderer2D::DrawTexture(Reme::Texture::Default, 200.0f, 200.0f, 50.0f, 50.0f);
		Reme::Renderer2D::PopState();

		// auto path = Reme::CreateRef<Reme::Path2D>();
		// path->MoveTo(100.0f, 100.0f);
		// path->LineTo(200.0f, 100.0f);
		// path->ArcTo(300.0f, 100.0f, 300.0f, 300.0f, 64.0f);
		// path->BezierCurveTo(400.0f, 200.0f, 500.0f, 400.0f, 600.0f, 300.0f);
		// path->LineTo(600.0f, 600.0f);
		// path->QuadraticCurveTo(400.0f, 700.0f, 200.0f, 600.0f);
		// path->Ellipse(200.0f, 200.0f, 100.0f, 50.0f, 0.0f, 0.0f, 6.28f);
		// path->Rect(0.0f, 0.0f, 50.0f, 50.0f);
		// Reme::Renderer2D::StrokePath(path, Reme::Color::Cyan);

		Reme::Renderer2D::End();
	}

	void OnImGuiRender() override
	{
		auto Width = Reme::Application::Get().GetWindow().GetWidth();
		auto Height = Reme::Application::Get().GetWindow().GetHeight();

		ImGui::Begin("Values");
		ImGui::DragFloat("Rotation", &rot, 1.0f, -180.0f, 180.0f);
		ImGui::End();

		ImGui::Begin("Menu");
		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
		ImGui::DragFloat("Img Width", &imgWidth, 1.0f, 10.0f, 1000.0f);
		ImGui::DragFloat("Rect Size", &rectSize, 1.0f, 10.0f, 1000.0f);

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
					<< "\tScreen res: " << Width << "x" << Height << std::endl
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

	void OnEvent(Reme::Event& e) override
	{
		Reme::EventDispatcher dispatcher(e);
		dispatcher.Dispatch<Reme::WindowResizeEvent>(REME_BIND_EVENT_FN(Test::OnResize));
	}

	bool OnResize(Reme::WindowResizeEvent e)
	{
		cam->SetProjection(0.0f, e.GetWidth(), e.GetHeight(), 0.0f);
		LOG_INFO("Screen resized, new resolution: {}x{}", e.GetWidth(), e.GetHeight());
		return true;
	}
private:
	float rot = 45.0f;
	std::ofstream fOut;
	std::array<char, 100> benchmarkName;
	std::array<char, 100> createdFileName;
	bool benchMarkStarted = false;
	float imgWidth = 50.0f;
	float rectSize = 50.0f;
	Reme::Ref<Reme::OrthographicCamera> cam;
	std::array<Reme::Ref<Reme::Texture>, 4> imgs;
	std::array<float, 250> avgFps;
};
