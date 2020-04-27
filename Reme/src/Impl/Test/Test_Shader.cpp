#include "RemePCH.h"
#include "Impl/Test/Test_Shader.h"
#include "Reme/Utility/Utils.h"

namespace Reme
{
    uint32_t Test_Shader::BindedShader = 0;

    Test_Shader::Test_Shader(const std::string& filePath)
    {
        std::unordered_map<uint32_t, std::string> sources;
        sources[VERTEX_SHADER] = ReadFile(filePath + ".vert");
        sources[FRAGMENT_SHADER] = ReadFile(filePath + ".frag");
        Compile(sources);

        // Extract name from filepath
        auto lastSlash = filePath.find_last_of("/\\");
        lastSlash = lastSlash == std::string::npos ? 0 : lastSlash + 1;
        auto lastDot = filePath.rfind('.');
        auto count = lastDot == std::string::npos ? filePath.size() - lastSlash : lastDot - lastSlash;
        m_Name = filePath.substr(lastSlash, count);
    }

    Test_Shader::Test_Shader(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc)
        : m_Name(name)
    {
        std::unordered_map<uint32_t, std::string> sources;
        sources[VERTEX_SHADER] = vertexSrc;
        sources[FRAGMENT_SHADER] = fragmentSrc;
        Compile(sources);
    }

    Test_Shader::~Test_Shader()
    {
    }

    void Test_Shader::Compile(const std::unordered_map<uint32_t, std::string>& shaderSources)
    {
        // TODO: Compile the shader for error
        // Then analyze its and check if the Uniform Setter is valid
    }
}
