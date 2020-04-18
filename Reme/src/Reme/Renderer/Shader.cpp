#include "reme_pch.h"
#include "Reme/Renderer/Shader.h"
#include "Reme/Renderer/RendererAPI.h"

#include "Impl/OpenGL/OpenGL_Shader.h"

namespace Reme
{
    Ref<Shader> Shader::Create(const std::string& filePath)
    {
        switch (RendererAPI::GetAPI())
		{
			case RendererAPI::None: CORE_ASSERT(false, "RendererAPI::None is not supported!"); return nullptr;
			case RendererAPI::OpenGL: return CreateRef<OpenGL_Shader>(filePath);
		}

		CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
    }

    Ref<Shader> Shader::Create(const std::string& name, const std::string& vertexShader, const std::string& fragmentShader)
    {
        switch (RendererAPI::GetAPI())
		{
			case RendererAPI::None: CORE_ASSERT(false, "RendererAPI::None is not supported!"); return nullptr;
			case RendererAPI::OpenGL: return CreateRef<OpenGL_Shader>(name, vertexShader, fragmentShader);
		}

		CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
    }
}
