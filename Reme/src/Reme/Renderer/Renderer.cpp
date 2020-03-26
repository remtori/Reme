#include "pch.h"
#include "Reme/Renderer/Renderer.h"
#include "Reme/Renderer/Renderer2D.h"
#include "Reme/Renderer/RendererAPI.h"

namespace Reme
{    
    void Renderer::Init()
    {
        RenderCommand::Init();
        Renderer2D::Init();
    }

    void Renderer::Shutdown()
    {
        Renderer2D::Shutdown();
    }

    void Renderer::OnWindowResize(float width, float height)
    {
        RenderCommand::SetViewport(0, 0, width, height);
    }
}
