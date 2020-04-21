#pragma once

#include "Reme/Renderer/Shader.h"
#include "Reme/Renderer/ShaderDataLayout.h"

#include <glm/glm.hpp>

#include <string>
#include <unordered_map>

namespace Reme
{
    class Test_Shader : public Shader
    {
    public:
        static uint32_t BindedShader;

        Test_Shader(const std::string& filePath);
        Test_Shader(const std::string& name, const std::string& vertexShader, const std::string& fragmentShader);
        ~Test_Shader();

        void Bind() const override { BindedShader = GetAssetID(); }
        void Unbind() const override { BindedShader = 0; }

        void SetInt(const std::string& name, int32_t value) override {}
        void SetIntArray(const std::string& name, const int32_t* const values, uint32_t count) override {}
        void SetFloat(const std::string& name, float value) override {}
        void SetFloat2(const std::string& name, const glm::vec2& value) override {}
        void SetFloat3(const std::string& name, const glm::vec3& value) override {}
        void SetFloat4(const std::string& name, const glm::vec4& value) override {}
        void SetMat3(const std::string& name, const glm::mat3& matrix) override {}
        void SetMat4(const std::string& name, const glm::mat4& matrix) override {}

        const std::string& GetName() const override { return m_Name; }

        enum {
            VERTEX_SHADER,
            FRAGMENT_SHADER,
        };
    private:
        void Compile(const std::unordered_map<uint32_t, std::string>& shaderSources);
        std::string m_Name;
    };
}
