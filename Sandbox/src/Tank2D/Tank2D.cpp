#include "Tank2D.h"

#include <Reme.h>
#include <imgui/imgui.h>

#include <glm/glm.hpp>

using namespace Reme;

#include "Settings.h"
#include "Tank.h"

Tank tank;

void Tank2D::OnAttach()
{
	m_LayerName = "Tank2D";
	auto Width = Application::Get().GetWindow().GetWidth();
	auto Height = Application::Get().GetWindow().GetHeight();

	tank.pos = { Width / 2.0f, Height / 2.0f };
	cam = CreateRef<OrthographicCamera>(0.0f, Width, Height, 0.0f);		
	RenderCommand::SetClearColor(Color::Black);
}

void Tank2D::OnUpdate(float elapsedTime)
{	
	auto Width = Application::Get().GetWindow().GetWidth();
	auto Height = Application::Get().GetWindow().GetHeight();
	glm::vec2 HALF_SCREEN(Width / 2.0f, Height / 2.0f);

	tank.Update(elapsedTime);

	cam->SetPosition(glm::vec3(tank.pos - HALF_SCREEN, 0.0f));
}

void Tank2D::OnRender()
{
	Renderer2D::Begin(cam);

	Renderer2D::DrawRect(Color::White, 0.0f, 0.0f, 1000.0f, 1000.0f);

	tank.Render();
	
	Renderer2D::End();
}

void Tank2D::OnImGuiRender()
{
	auto Width = Application::Get().GetWindow().GetWidth();
	auto Height = Application::Get().GetWindow().GetHeight();

	ImGui::Begin("Tank Stats");
	ImGui::Text("Position: %.2f %.2f", tank.pos.x, tank.pos.y);
	ImGui::Text("Velocity: %.2f %.2f (%.2f)", tank.vel.x, tank.vel.y, glm::length(tank.vel));
	ImGui::DragFloat("Barrel Rot", &tank.barrelRotation, 0.001, 0.0f, 6.28f);
	ImGui::DragFloat("Speed", &Settings::speed);
	ImGui::DragFloat("Rot Speed", &Settings::rotSpeed, 0.001f, 0.0f, 10.0f);
	ImGui::DragFloat("Friction", &Settings::FRICTION, 0.001f, 0.0f, 1.0f);
	ImGui::End();
}

void Tank2D::OnEvent(Event& e)
{
	EventDispatcher dispatcher(e);
	dispatcher.Dispatch<WindowResizeEvent>(BIND_EVENT_FN(Tank2D::OnResize));
}

bool Tank2D::OnResize(WindowResizeEvent e)
{
	cam->SetProjection(0.0f, e.GetWidth(), e.GetHeight(), 0.0f);
	LOG_INFO("Screen resized, new resolution: {}x{}", e.GetWidth(), e.GetHeight());
	return true;
}