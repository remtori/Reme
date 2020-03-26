#include "pch.h"
#include "Reme/Renderer/Renderer.h"
#include "Reme/Renderer/Renderer2D.h"

#include <glad/glad.h>

namespace Reme
{
    void Renderer::Init()
    {
        Renderer2D::Init();
    }

    void Renderer::Shutdown()
    {
        Renderer2D::Shutdown();
    }

    void Renderer::OnWindowResize(float width, float height)
    {
        glViewport(0, 0, width, height);
    }
}
