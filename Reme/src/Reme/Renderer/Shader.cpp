#include "RemePCH.h"
#include "Reme/Renderer/Shader.h"
#include "Reme/Renderer/RendererAPI.h"

#ifdef TEST
#include "Impl/Test/Test_Shader.h"
#endif
#include "Impl/OpenGL/OpenGL_Shader.h"

namespace Reme
{
    Ref<Shader> Shader::Create(const std::string& filePath)
    {
        switch (RendererAPI::GetAPI())
		{
			case RendererAPI::None: CORE_ASSERT(false, "RendererAPI::None is not supported!"); return nullptr;
			case RendererAPI::OpenGL: return CreateRef<OpenGL_Shader>(filePath);
#ifdef TEST
			case RendererAPI::Test: return CreateRef<Test_Shader>(filePath);
#endif
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
#ifdef TEST
			case RendererAPI::Test: return CreateRef<Test_Shader>(name, vertexShader, fragmentShader);
#endif
		}

		CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
    }
}
