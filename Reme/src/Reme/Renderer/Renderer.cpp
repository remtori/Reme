#include "reme_pch.h"
#include "Reme/Renderer/Renderer.h"
#include "Reme/Renderer/RendererAPI.h"
#include "Reme/Renderer/Renderer2D.h"

namespace Reme
{
    void Renderer::Init()
    {
        // The order of these is important
        RenderCommand::Init();
        Renderer2D::Init();
        Texture::Init();
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
