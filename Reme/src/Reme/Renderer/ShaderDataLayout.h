#pragma once

namespace Reme
{
	enum class ShaderDataType
	{
		Float, Float2, Float3, Float4, Mat2, Mat3, Mat4, Int, Int2, Int3, Int4
	};

	static uint32_t ShaderDataTypeSize(ShaderDataType type)
	{
		switch (type)
		{
		case ShaderDataType::Float:    return 4;
		case ShaderDataType::Float2:   return 4 * 2;
		case ShaderDataType::Float3:   return 4 * 3;
		case ShaderDataType::Float4:   return 4 * 4;
		case ShaderDataType::Int:      return 4;
		case ShaderDataType::Int2:     return 4 * 2;
		case ShaderDataType::Int3:     return 4 * 3;
		case ShaderDataType::Int4:     return 4 * 4;

		// Matrix type get handle specially in VertexArray impl
		// Under the hood Matrix type in attribute
		// is the same as Float2[2] for Mat2, Float3[3] for Mat3, ...
		// the fn ExpandDataType will duplicate those as needed
		// we just need to trick it the same as Float2, Float3, ... in this function
		case ShaderDataType::Mat2:     return 4 * 2;
		case ShaderDataType::Mat3:     return 4 * 3;
		case ShaderDataType::Mat4:     return 4 * 4;
		}

		CORE_ASSERT(false, "Unknown ShaderDataType!");
		return 0;
	}

	struct BufferElement
	{
		ShaderDataType Type;
		std::string Name;
		uint32_t Size;
		uint32_t Offset;
		bool Normalized;
		uint32_t Divisor;

		BufferElement(ShaderDataType type, const std::string& name, bool normalized = false, uint32_t divisor = 0)
			: Type(type), Name(name), Normalized(normalized), Divisor(divisor), Offset(0), Size(ShaderDataTypeSize(type))
		{
		}

		uint32_t GetComponentCount() const
		{
			switch (Type)
			{
			case ShaderDataType::Float:   return 1;
			case ShaderDataType::Float2:  return 2;
			case ShaderDataType::Float3:  return 3;
			case ShaderDataType::Float4:  return 4;

			// These won't get called, ever
			// case ShaderDataType::Mat2:    return 2;
			// case ShaderDataType::Mat3:    return 3;
			// case ShaderDataType::Mat4:    return 4;

			case ShaderDataType::Int:      return 1;
			case ShaderDataType::Int2:     return 2;
			case ShaderDataType::Int3:     return 3;
			case ShaderDataType::Int4:     return 4;
			}

			CORE_ASSERT(false, "Unknown ShaderDataType!");
			return 0;
		}
	};

	class BufferLayout
	{
	public:
		BufferLayout() {}

		BufferLayout(const std::initializer_list<BufferElement>& elements)
			: m_Elements(elements)
		{
			ExpandDataType();
			CalculateOffsetsAndStride();
		}

		inline uint32_t GetStride() const { return m_Stride; }
		inline const std::vector<BufferElement>& GetElements() const { return m_Elements; }

		std::vector<BufferElement>::iterator begin() { return m_Elements.begin(); }
		std::vector<BufferElement>::iterator end() { return m_Elements.end(); }
		std::vector<BufferElement>::const_iterator begin() const { return m_Elements.begin(); }
		std::vector<BufferElement>::const_iterator end() const { return m_Elements.end(); }
	private:
		void ExpandDataType()
		{
			std::vector<BufferElement> newElements;
			ShaderDataType type;
			uint8_t loop, i;
			for (auto& element : m_Elements)
			{
				switch (element.Type)
				{
					case ShaderDataType::Mat2:
						loop = 2;
						type = ShaderDataType::Float2;
						break;
					case ShaderDataType::Mat3:
						loop = 3;
						type = ShaderDataType::Float3;
						break;
					case ShaderDataType::Mat4:
						loop = 4;
						type = ShaderDataType::Float4;
						break;
					default:
						newElements.push_back(element);
						continue;
				}

				for (i = 0; i < loop; i++)
				{
					newElements.push_back({
						type, element.Name, element.Normalized, element.Divisor
					});
				}
			}

			m_Elements = newElements;
		}

		void CalculateOffsetsAndStride()
		{
			uint32_t offset = 0;
			m_Stride = 0;
			for (auto& element : m_Elements)
			{
				element.Offset = offset;
				offset += element.Size;
				m_Stride += element.Size;
			}
		}
	private:
		std::vector<BufferElement> m_Elements;
		uint32_t m_Stride = 0;
	};
}
