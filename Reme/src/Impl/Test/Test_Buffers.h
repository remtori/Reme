#pragma once

#include "Reme/Renderer/Buffers.h"
#include "Reme/Renderer/ShaderDataLayout.h"

namespace Reme
{
	class Test_VertexBuffer : public VertexBuffer
	{
	public:
		static uint32_t BindedVBO;

		Test_VertexBuffer(uint32_t byteCount, bool isStatic);
		~Test_VertexBuffer();

		void Bind() override { BindedVBO = GetAssetID(); }
		void Unbind() override { BindedVBO = 0; }
		bool IsBinded() { return BindedVBO == GetAssetID(); }

		void SetData(float* data, uint32_t byteOffset, uint32_t byteCount) override;
		const std::vector<float>& GetData() const { return m_Data; }
	private:
		std::vector<float> m_Data;
	};


	class Test_IndexBuffer : public IndexBuffer
	{
	public:
		static uint32_t BindedIBO;

		Test_IndexBuffer(uint32_t byteCount, bool isStatic);
		~Test_IndexBuffer();

		void Bind() override { BindedIBO = GetAssetID(); }
		void Unbind() override { BindedIBO = 0; }
		bool IsBinded() { return BindedIBO == GetAssetID(); }

		void SetData(uint32_t* data, uint32_t byteOffset, uint32_t byteCount) override;
		const std::vector<uint32_t>& GetData() const { return m_Data; }
	private:
		std::vector<uint32_t> m_Data;
	};
}

