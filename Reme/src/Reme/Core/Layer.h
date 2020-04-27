#pragma once

#include "Reme/Events/Event.h"

namespace Reme
{
    class Layer
    {
    public:
		Layer(const std::string& name = "Layer") : m_LayerName(name) {};
		virtual ~Layer() = default;

		virtual void OnAttach() {}
		virtual void OnDetach() {}

		/**
		 * OnRender function only being called when we draw a new frame
		 */
		virtual void OnRender() {}

		/**
		 * OnUpdate is guarantee to run every "DeltaTime", which default to 1/60 of a second
		 */
		virtual void OnUpdate(float elapsedTime) {}

		virtual void OnImGuiRender() {}

		virtual void OnEvent(Event& e) {}

		inline const std::string& GetName() const { return m_LayerName; }
	protected:
		std::string m_LayerName;
    };
}
