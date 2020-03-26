#include "pch.h"
#include "Reme/Renderer/Shader.h"
#include "Reme/Renderer/RendererAPI.h"

#include "Impl/OpenGL/OpenGL_Shader.h"

namespace Reme
{
    Shader* Shader::Create(const std::string& filePath)
    {
        switch (RendererAPI::GetAPI())
		{
			case RendererAPI::None: REME_ASSERT(false, "RendererAPI::None is not supported!"); return nullptr;
			case RendererAPI::OpenGL: return new OpenGL_Shader(filePath);
		}

		REME_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
    }

    Shader* Shader::Create(const std::string& name, const std::string& vertexShader, const std::string& fragmentShader)
    {
        switch (RendererAPI::GetAPI())
		{
			case RendererAPI::None: REME_ASSERT(false, "RendererAPI::None is not supported!"); return nullptr;
			case RendererAPI::OpenGL: return new OpenGL_Shader(name, vertexShader, fragmentShader);
		}

		REME_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
    }
}
