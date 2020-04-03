#include "Tank.h"

#include <Reme.h>
#include <glm/gtx/rotate_vector.hpp>

using namespace Reme;

#include "Settings.h"

const float PI = glm::pi<float>();

float ClampAngle(float a)
{
	while (a > 2 * PI) a -= 2 * PI;
	while (a < 0.0f) a += 2 * PI;
	return  a;
}

Tank::Tank()
    : pos(0.0f), vel(0.0f),
    rotation(0.0f), barrelRotation(0.0f)
{
}

Tank::~Tank()
{
}

void Tank::Update(float elapsedTime)
{
    auto Width = Application::Get().GetWindow().GetWidth();
	auto Height = Application::Get().GetWindow().GetHeight();
	glm::vec2 HALF_SCREEN(Width / 2.0f, Height / 2.0f);

    if (Input::IsKeyPressed(KeyCode::A)) rotation -= Settings::rotSpeed * elapsedTime;
    if (Input::IsKeyPressed(KeyCode::D)) rotation += Settings::rotSpeed * elapsedTime;

    glm::vec2 acc = { Settings::speed * elapsedTime, 0.0f };
    acc = glm::rotate(acc, rotation);
    
    if (Input::IsKeyPressed(KeyCode::W)) vel += acc;
    if (Input::IsKeyPressed(KeyCode::S)) vel -= acc;

    vel *= glm::pow(1.0f - Settings::FRICTION, elapsedTime);
    if (glm::length(vel) < 0.01f) vel = glm::vec2(0.0f);

    pos += vel * elapsedTime;
    
    glm::vec2 barrelV = HALF_SCREEN - Input::GetMousePos();
    float targetAngle = glm::atan(barrelV.y / barrelV.x) + PI * (1 + (barrelV.x < 0.0f));
    targetAngle = ClampAngle(targetAngle);
    float deltaAngle = targetAngle - barrelRotation;

    if (glm::abs(deltaAngle) < Settings::barrelRotSpeed * elapsedTime)
    {
        barrelRotation = targetAngle;
    }
    else if (deltaAngle > PI ||  (- PI < deltaAngle && deltaAngle < 0.0f))
    {
        barrelRotation -= Settings::barrelRotSpeed * elapsedTime;
    } 
    else 
    {		
        barrelRotation += Settings::barrelRotSpeed * elapsedTime;
    }

    barrelRotation = ClampAngle(barrelRotation);
}

void Tank::Render()
{    
	Renderer2D::PushState();
	Renderer2D::Translate(pos.x, pos.y);
	Renderer2D::Rotate(rotation);
	Renderer2D::DrawRect(Color::Red, -25.0f, -15.0f, 50.f, 30.0f);
	Renderer2D::PopState();

	Renderer2D::PushState();
	Renderer2D::Translate(pos.x, pos.y);
	Renderer2D::Rotate(barrelRotation);
	Renderer2D::DrawRect(Color::Blue, 0.0f, -5.0f, 45.0f, 10.0f);
	Renderer2D::PopState();
}
