#pragma once

#include "Reme/Core/AssetManager.h"

#include <string>
#include <unordered_map>
#include <glm/glm.hpp>

namespace Reme
{
    class Shader : public Asset
    {
    public:
        static Ref<Shader> Create(const std::string& filePath);
        static Ref<Shader> Create(const std::string& name, const std::string& vertexShader, const std::string& fragmentShader);
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
