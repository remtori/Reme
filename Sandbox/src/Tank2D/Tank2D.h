#pragma once

#include <Reme.h>

class Tank2D : public Reme::Layer
{
public:
	void OnAttach() override;
	void OnUpdate(float elapsedTime) override;
	void OnRender() override;
	void OnImGuiRender() override;
	void OnEvent(Reme::Event& e) override;
	bool OnResize(Reme::WindowResizeEvent e);
private:
	Reme::Ref<Reme::OrthographicCamera> cam;
};
