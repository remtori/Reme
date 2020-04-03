#pragma once

#include "Reme/Renderer/Shader.h"

#include <glm/glm.hpp>

#include <string>
#include <unordered_map>

namespace Reme
{
    class OpenGL_Shader : public Shader
    {
    public:
        OpenGL_Shader(const std::string& filePath);
        OpenGL_Shader(const std::string& name, const std::string& vertexShader, const std::string& fragmentShader);
    public:
        ~OpenGL_Shader();

        void Bind() const override;
        void Unbind() const override;

        void SetInt(const std::string& name, int32_t value) override;
        void SetIntArray(const std::string& name, const int32_t* const values, uint32_t count) override;

        void SetFloat(const std::string& name, float value) override;
        void SetFloat2(const std::string& name, const glm::vec2& value) override;
        void SetFloat3(const std::string& name, const glm::vec3& value) override;
        void SetFloat4(const std::string& name, const glm::vec4& value) override;

        void SetMat3(const std::string& name, const glm::mat3& matrix) override;
        void SetMat4(const std::string& name, const glm::mat4& matrix) override;

        const std::string& GetName() const override { return m_Name; }

    private:
        int32_t GetUniformLocation(const std::string& name);
        void Compile(const std::unordered_map<uint32_t, std::string>& shaderSources);
    private:
        uint32_t m_ProgramID;
        std::string m_Name;
        std::unordered_map<std::string, int32_t> m_UniformLocation;
    };
}
