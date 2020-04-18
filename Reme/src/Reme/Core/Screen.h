#pragma once

#include "Reme/Core/LayerStack.h"

namespace Reme
{
    class Screen
    {
    public:
        void OnEvent(Event& event);
        void OnUpdate(float elapsedTime);
        void OnRender();
        void OnImGuiRender();

        inline void PushLayer(Layer* layer) { m_LayerStack.PushLayer(layer); }
        inline void PushOverlay(Layer* overlay) { m_LayerStack.PushOverlay(overlay); }

        inline void PopLayer(Layer* layer) { m_LayerStack.PopLayer(layer); }
        inline void PopOverlay(Layer* overlay) { m_LayerStack.PopOverlay(overlay); }
    private:
        LayerStack m_LayerStack;
    };
}
