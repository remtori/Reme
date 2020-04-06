#pragma once

#include "Reme/Core/Core.h"

#include <glm/glm.hpp>
#include <string>
#include <unordered_map>

namespace Reme
{
    class Shader
    {
    public:
        static Scope<Shader> Create(const std::string& filePath);
        static Scope<Shader> Create(const std::string& name, const std::string& vertexShader, const std::string& fragmentShader);
    public:

        virtual void Bind() const = 0;
        virtual void Unbind() const = 0;

        virtual void SetInt(const std::string& name, int32_t value) = 0;
        virtual void SetIntArray(const std::string& name, const int32_t* const values, uint32_t count) = 0;
        virtual void SetFloat(const std::string& name, float value) = 0;
        virtual void SetFloat2(const std::string& name, const glm::vec2& value) = 0;
        virtual void SetFloat3(const std::string& name, const glm::vec3& value) = 0;
        virtual void SetFloat4(const std::string& name, const glm::vec4& value) = 0;

        virtual void SetMat3(const std::string& name, const glm::mat3& matrix) = 0;
        virtual void SetMat4(const std::string& name, const glm::mat4& matrix) = 0;

        virtual const std::string& GetName() const = 0;
    };
}
