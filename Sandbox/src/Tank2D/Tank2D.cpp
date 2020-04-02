#include "Tank2D.h"

#include <Reme.h>
#include <imgui/imgui.h>

#include <glm/glm.hpp>
#include <glm/gtx/vector_angle.hpp>
#include <glm/gtx/rotate_vector.hpp>

using namespace Reme;

struct Tank
{
	glm::vec2 pos;
	glm::vec2 vel;
	float barrelRot = 0.0f;
	float tankRot = 0.0f;
};

Tank tank;
float speed = 500.0f;
float rotSpeed = 1.62f;
float bRotSpeed = 2.00f;
float FRICTION = 0.995f;

const float PI = glm::pi<float>();

float ClampAngle(float a)
{
	while (a > 2 * PI) a -= 2 * PI;
	while (a < 0.0f) a += 2 * PI;
	return  a;
}

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

	if (Input::IsKeyPressed(KeyCode::A)) tank.tankRot -= rotSpeed * elapsedTime;
	if (Input::IsKeyPressed(KeyCode::D)) tank.tankRot += rotSpeed * elapsedTime;

	glm::vec2 acc = { speed * elapsedTime, 0.0f };
	acc = glm::rotate(acc, tank.tankRot);
	
	if (Input::IsKeyPressed(KeyCode::W)) tank.vel += acc;
	if (Input::IsKeyPressed(KeyCode::S)) tank.vel -= acc;

	tank.vel *= glm::pow(1.0f - FRICTION, elapsedTime);
	if (glm::length(tank.vel) < 0.01f) tank.vel = glm::vec2(0.0f);

	tank.pos += tank.vel * elapsedTime;
	cam->SetPosition(glm::vec3(tank.pos - HALF_SCREEN, 0.0f));
	
	glm::vec2 barrelV = HALF_SCREEN - Input::GetMousePos();
	float targetAngle = glm::atan(barrelV.y / barrelV.x) + PI * (1 + (barrelV.x < 0.0f));
	targetAngle = ClampAngle(targetAngle);
	float deltaAngle = targetAngle - tank.barrelRot;

	if (glm::abs(deltaAngle) < bRotSpeed * elapsedTime)
	{
		tank.barrelRot = targetAngle;
	}
	else if (deltaAngle > PI ||  (- PI < deltaAngle && deltaAngle < 0.0f))
	{
		tank.barrelRot -= bRotSpeed * elapsedTime;
	} 
	else 
	{		
		tank.barrelRot += bRotSpeed * elapsedTime;
	}

	tank.barrelRot = ClampAngle(tank.barrelRot);
}

void Tank2D::OnRender()
{
	Renderer2D::Begin(cam);

	Renderer2D::DrawRect(Color::White, 0.0f, 0.0f, 1000.0f, 1000.0f);

	Renderer2D::PushState();
	Renderer2D::Translate(tank.pos.x, tank.pos.y);
	Renderer2D::Rotate(tank.tankRot);
	Renderer2D::DrawRect(Color::Red, -25.0f, -15.0f, 50.f, 30.0f);
	Renderer2D::PopState();

	Renderer2D::PushState();
	Renderer2D::Translate(tank.pos.x, tank.pos.y);
	Renderer2D::Rotate(tank.barrelRot);
	Renderer2D::DrawRect(Color::Blue, 0.0f, -5.0f, 75.0f, 10.0f);
	Renderer2D::PopState();
	
	Renderer2D::End();
}

void Tank2D::OnImGuiRender()
{
	auto Width = Application::Get().GetWindow().GetWidth();
	auto Height = Application::Get().GetWindow().GetHeight();

	ImGui::Begin("Tank Stats");
	ImGui::Text("Position: %.2f %.2f", tank.pos.x, tank.pos.y);
	ImGui::Text("Velocity: %.2f %.2f (%.2f)", tank.vel.x, tank.vel.y, glm::length(tank.vel));
	ImGui::DragFloat("Barrel Rot", &tank.barrelRot, 0.001, 0.0f, 2 * glm::pi<float>());
	ImGui::DragFloat("Speed", &speed);
	ImGui::DragFloat("Rot Speed", &rotSpeed, 0.001f, 0.0f, 10.0f);
	ImGui::DragFloat("Friction", &FRICTION, 0.001f, 0.0f, 1.0f);
	ImGui::End();
}

void Tank2D::OnEvent(Event& e)
{
	EventDispatcher dispatcher(e);
	dispatcher.Dispatch<WindowResizeEvent>(REME_BIND_EVENT_FN(Tank2D::OnResize));
}

bool Tank2D::OnResize(WindowResizeEvent e)
{
	cam->SetProjection(0.0f, e.GetWidth(), e.GetHeight(), 0.0f);
	LOG_INFO("Screen resized, new resolution: {}x{}", e.GetWidth(), e.GetHeight());
	return true;
}