#include "pch.h"
#include "Reme/Screen/LayerStack.h"

namespace Reme
{
    LayerStack::~LayerStack()
    {
        for (Layer* layer : m_Layers)
        {
            layer->OnDetach();
        }
    }

    void LayerStack::PushLayer(Layer* layer)
    {
        layer->OnAttach();
        m_Layers.emplace(m_Layers.begin() + m_InsertIndex, layer);
        m_InsertIndex++;
    }

    void LayerStack::PushOverlay(Layer* overlay)
    {
        overlay->OnAttach();
        m_Layers.emplace_back(overlay);
    }

    void LayerStack::PopLayer(Layer* layer)
    {
        auto it = std::find(m_Layers.begin(), m_Layers.begin() + m_InsertIndex, layer);
        if (it != m_Layers.begin() + m_InsertIndex)
        {
            layer->OnDetach();
            m_Layers.erase(it);
            m_InsertIndex--;
        }
    }

    void LayerStack::PopOverlay(Layer* overlay)
    {
        auto it = std::find(m_Layers.begin() + m_InsertIndex, m_Layers.end(), overlay);
		if (it != m_Layers.end())
		{
            overlay->OnDetach();
			m_Layers.erase(it);
		}
    }
}
