#include "RemePCH.h"
#include "Reme/Core/LayerStack.h"

namespace Reme
{
    LayerStack::~LayerStack()
    {
        PROFILE_FUNCTION();

        for (Layer* layer : m_Layers)
        {
            layer->OnDetach();
        }
    }

    void LayerStack::PushLayer(Layer* layer)
    {
        PROFILE_FUNCTION();

        layer->OnAttach();
        m_Layers.emplace(m_Layers.begin() + m_InsertIndex, layer);
        m_InsertIndex++;
    }

    void LayerStack::PushOverlay(Layer* overlay)
    {
        PROFILE_FUNCTION();

        overlay->OnAttach();
        m_Layers.emplace_back(overlay);
    }

    void LayerStack::PopLayer(Layer* layer)
    {
        PROFILE_FUNCTION();

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
        PROFILE_FUNCTION();
        
        auto it = std::find(m_Layers.begin() + m_InsertIndex, m_Layers.end(), overlay);
		if (it != m_Layers.end())
		{
            overlay->OnDetach();
			m_Layers.erase(it);
		}
    }
}
