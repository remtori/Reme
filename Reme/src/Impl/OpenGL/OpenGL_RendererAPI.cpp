#include "pch.h"
#include "Impl/OpenGL/OpenGL_RendererAPI.h"

#include <glad/glad.h>

namespace Reme
{
    void OpenGL_RendererAPI::Init()
    {        
		glDisable(GL_DEPTH_TEST);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    }

    void OpenGL_RendererAPI::SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
    {
        glViewport(x, y, width, height);
    }

    void OpenGL_RendererAPI::SetClearColor(const Color& color)
    {
        glClearColor(color.r / 255.0f, color.g / 255.0f, color.b / 255.0f, color.a / 255.0f);
    }

    void OpenGL_RendererAPI::Clear()
    {
        glClear(GL_COLOR_BUFFER_BIT);
    }

    void OpenGL_RendererAPI::PollError()
    {
		GLenum err;
		while ((err = glGetError()) != GL_NO_ERROR)
		{
			CORE_LOG_ERROR("OpenGL Error: {}", err);
		}
    }

    void OpenGL_RendererAPI::DrawIndexed(uint32_t count, uint32_t offset)
    {
        glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, (void*) offset);
    }

    void OpenGL_RendererAPI::DrawArrays(uint32_t count, uint32_t offset)
    {
        glDrawArrays(GL_TRIANGLES, offset, count);
    }
}