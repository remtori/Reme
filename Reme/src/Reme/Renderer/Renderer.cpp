#include "reme_pch.h"
#include "Reme/Renderer/Renderer.h"
#include "Reme/Renderer/RendererAPI.h"
#include "Reme/Renderer/Renderer2D.h"

namespace Reme
{
    void Renderer::Init()
    {
        PROFILE_FUNCTION();
        
        // The order of these is important
        RenderCommand::Init();
        Renderer2D::Init();
        Texture::Init();
    }

    void Renderer::Shutdown()
    {
        PROFILE_FUNCTION();

        Renderer2D::Shutdown();
    }

    void Renderer::OnWindowResize(float width, float height)
    {
        PROFILE_FUNCTION();
        
        RenderCommand::SetViewport(0, 0, width, height);
    }
}
