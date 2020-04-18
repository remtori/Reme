#include "reme_pch.h"
#include "Reme/Core/Screen.h"

namespace Reme
{
	void Screen::OnEvent(Event& event)
	{
		for (auto it = m_LayerStack.rbegin(); it != m_LayerStack.rend(); ++it)
		{
			(*it)->OnEvent(event);
			if (event.Handled) break;
		}
	}

	void Screen::OnUpdate(float elapsedTime)
	{
		for (Layer* layer : m_LayerStack)
		{
			layer->OnUpdate(elapsedTime);
		}
	}

	void Screen::OnRender()
	{
		for (Layer* layer : m_LayerStack)
		{
			layer->OnRender();
		}
	}

	void Screen::OnImGuiRender()
	{
		for (Layer* layer : m_LayerStack)
		{
			layer->OnImGuiRender();
		}
	}
}