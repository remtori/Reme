#include "pch.h"
#include "Reme/Screen/Screen.h"

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

	void Screen::OnUpdate(float ellapsedTime)
	{
		for (Layer* layer : m_LayerStack)
		{
			layer->OnUpdate(ellapsedTime);
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
