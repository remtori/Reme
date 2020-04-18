#include "RemePCH.h"
#include "Impl/OpenGL/OpenGL_Shader.h"
#include "Reme/Utility/Utils.h"

#include <glad/glad.h>
#include <fstream>
#include <glm/gtc/type_ptr.hpp>

namespace Reme
{
    OpenGL_Shader::OpenGL_Shader(const std::string& filePath)
    {
        std::unordered_map<uint32_t, std::string> sources;
        sources[GL_VERTEX_SHADER] = ReadFile(filePath + ".vert");
        sources[GL_FRAGMENT_SHADER] = ReadFile(filePath + ".frag");
        Compile(sources);

        // Extract name from filepath
        auto lastSlash = filePath.find_last_of("/\\");
        lastSlash = lastSlash == std::string::npos ? 0 : lastSlash + 1;
        auto lastDot = filePath.rfind('.');
        auto count = lastDot == std::string::npos ? filePath.size() - lastSlash : lastDot - lastSlash;
        m_Name = filePath.substr(lastSlash, count);
    }

    OpenGL_Shader::OpenGL_Shader(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc)
        : m_Name(name)
    {
        std::unordered_map<uint32_t, std::string> sources;
        sources[GL_VERTEX_SHADER] = vertexSrc;
        sources[GL_FRAGMENT_SHADER] = fragmentSrc;
        Compile(sources);
    }

    OpenGL_Shader::~OpenGL_Shader()
    {
        glDeleteProgram(m_ProgramID);
    }

    void OpenGL_Shader::Compile(const std::unordered_map<uint32_t, std::string>& shaderSources)
    {
        m_ProgramID = glCreateProgram();
        std::array<uint32_t, 2> glShaderIDs;

        int glShaderIDIndex = 0;
        for (auto& kv : shaderSources)
        {
            GLenum type = kv.first;
            const std::string& source = kv.second;

            GLuint shader = glCreateShader(type);

            const GLchar* sourceCStr = source.c_str();
            glShaderSource(shader, 1, &sourceCStr, 0);

            glCompileShader(shader);

            GLint isCompiled = 0;
            glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
            if (isCompiled == GL_FALSE)
            {
                GLint maxLength = 0;
                glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

                std::vector<GLchar> infoLog(maxLength);
                glGetShaderInfoLog(shader, maxLength, &maxLength, &infoLog[0]);

                glDeleteShader(shader);

                CORE_LOG_ERROR("{0}", infoLog.data());
                CORE_ASSERT(false, "Shader compilation failure!");
                break;
            }

            glAttachShader(m_ProgramID, shader);
            glShaderIDs[glShaderIDIndex++] = shader;
        }

        glLinkProgram(m_ProgramID);

        GLint isLinked = 0;
        glGetProgramiv(m_ProgramID, GL_LINK_STATUS, (int*)&isLinked);
        if (isLinked == GL_FALSE)
        {
            GLint maxLength = 0;
            glGetProgramiv(m_ProgramID, GL_INFO_LOG_LENGTH, &maxLength);

            // The maxLength includes the NULL character
            std::vector<GLchar> infoLog(maxLength);
            glGetProgramInfoLog(m_ProgramID, maxLength, &maxLength, &infoLog[0]);

            glDeleteProgram(m_ProgramID);

            for (auto id : glShaderIDs)
                glDeleteShader(id);

            CORE_LOG_ERROR("{0}", infoLog.data());
            CORE_ASSERT(false, "Shader link failure!");
            return;
        }

        for (auto id : glShaderIDs)
        {
            glDetachShader(m_ProgramID, id);
            glDeleteShader(id);
        }
    }

    void OpenGL_Shader::Bind() const
    {
        glUseProgram(m_ProgramID);
    }

    void OpenGL_Shader::Unbind() const
    {
        glUseProgram(0);
    }

    GLint OpenGL_Shader::GetUniformLocation(const std::string& name)
    {
        GLint location;
        auto it = m_UniformLocation.find(name);

        if (it == m_UniformLocation.cend())
        {
            location = glGetUniformLocation(m_ProgramID, name.c_str());
            CORE_LOG_TRACE("Uniform Location '{}' = {}", name, location);
            m_UniformLocation.insert({ name, location });
        }
        else
            location = it->second;

        return location;
    }

    void OpenGL_Shader::SetInt(const std::string& name, int32_t value)
    {
        glUniform1i(OpenGL_Shader::GetUniformLocation(name), value);
    }

    void OpenGL_Shader::SetIntArray(const std::string& name, const int32_t* const values, uint32_t count)
    {
        glUniform1iv(OpenGL_Shader::GetUniformLocation(name), count, values);
    }

    void OpenGL_Shader::SetFloat(const std::string& name, float value)
    {
        glUniform1f(OpenGL_Shader::GetUniformLocation(name), value);
    }

    void OpenGL_Shader::SetFloat2(const std::string& name, const glm::vec2& value)
    {
        glUniform2f(OpenGL_Shader::GetUniformLocation(name), value.x, value.y);
    }

    void OpenGL_Shader::SetFloat3(const std::string& name, const glm::vec3& value)
    {
        glUniform3f(
            OpenGL_Shader::GetUniformLocation(name),
            value.x, value.y, value.z
        );
    }

    void OpenGL_Shader::SetFloat4(const std::string& name, const glm::vec4& value)
    {
        glUniform4f(
            OpenGL_Shader::GetUniformLocation(name),
            value.x, value.y, value.z, value.w
        );
    }

    void OpenGL_Shader::SetMat3(const std::string& name, const glm::mat3& matrix)
    {
        glUniformMatrix3fv(
            OpenGL_Shader::GetUniformLocation(name),
            1, GL_FALSE, glm::value_ptr(matrix)
        );
    }

    void OpenGL_Shader::SetMat4(const std::string& name, const glm::mat4& matrix)
    {
        glUniformMatrix4fv(
            OpenGL_Shader::GetUniformLocation(name),
            1, GL_FALSE, glm::value_ptr(matrix)
        );
    }
}
