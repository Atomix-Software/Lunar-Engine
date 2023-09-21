#include <lnapch.h>
#include "OpenGLVertexArray.h"

#include <glad/glad.h>

namespace luna
{
    static GLenum ShaderDataTypeToGLBaseType(ShaderDataType type)
    {
        switch (type)
        {
            case luna::ShaderDataType::Bool:   return GL_BOOL;
            case luna::ShaderDataType::Mat3:   return GL_FLOAT;
            case luna::ShaderDataType::Mat4:   return GL_FLOAT;
            case luna::ShaderDataType::Int:    return GL_INT;
            case luna::ShaderDataType::Int2:   return GL_INT;
            case luna::ShaderDataType::Int3:   return GL_INT;
            case luna::ShaderDataType::Int4:   return GL_INT;
            case luna::ShaderDataType::Float:  return GL_FLOAT;
            case luna::ShaderDataType::Float2: return GL_FLOAT;
            case luna::ShaderDataType::Float3: return GL_FLOAT;
            case luna::ShaderDataType::Float4: return GL_FLOAT;
        }

        LNA_CORE_ASSERT(false, "Unknown ShaderDataType!");
        return 0;
    }

    OpenGLVertexArray::OpenGLVertexArray()
    {
        LNA_PROFILE_FUNCTION();
        glCreateVertexArrays(1, &m_RendererID);
    }

    OpenGLVertexArray::~OpenGLVertexArray()
    {
		LNA_PROFILE_FUNCTION();
        glDeleteVertexArrays(1, &m_RendererID);
    }

    void OpenGLVertexArray::Bind() const
    {
		LNA_PROFILE_FUNCTION();
        glBindVertexArray(m_RendererID);
    }

    void OpenGLVertexArray::UnBind() const
    {
		LNA_PROFILE_FUNCTION();
        glBindVertexArray(0);
    }

    void OpenGLVertexArray::AddVertexBuffer(Shared<VertexBuffer>& buffer)
    {
		LNA_PROFILE_FUNCTION();
        LNA_CORE_ASSERT(buffer->GetLayout().GetElements().size(), "Vertex Buffer has no defined layout!");
        glBindVertexArray(m_RendererID);
        buffer->Bind();

		const auto& layout = buffer->GetLayout();
		for (const auto& element : layout)
		{
			switch (element.Type)
			{
			case ShaderDataType::Float:
			case ShaderDataType::Float2:
			case ShaderDataType::Float3:
			case ShaderDataType::Float4:
			{
				glEnableVertexAttribArray(m_VertexBufferIndex);
				glVertexAttribPointer(m_VertexBufferIndex,
					element.GetComponentCount(),
					ShaderDataTypeToGLBaseType(element.Type),
					element.Normalized ? GL_TRUE : GL_FALSE,
					layout.GetStride(),
					(const void*)element.Offset);
				m_VertexBufferIndex++;
				break;
			}
			case ShaderDataType::Int:
			case ShaderDataType::Int2:
			case ShaderDataType::Int3:
			case ShaderDataType::Int4:
			case ShaderDataType::Bool:
			{
				glEnableVertexAttribArray(m_VertexBufferIndex);
				glVertexAttribIPointer(m_VertexBufferIndex,
					element.GetComponentCount(),
					ShaderDataTypeToGLBaseType(element.Type),
					layout.GetStride(),
					(const void*)element.Offset);
				m_VertexBufferIndex++;
				break;
			}
			case ShaderDataType::Mat3:
			case ShaderDataType::Mat4:
			{
				uint8_t count = element.GetComponentCount();
				for (uint8_t i = 0; i < count; i++)
				{
					glEnableVertexAttribArray(m_VertexBufferIndex);
					glVertexAttribPointer(m_VertexBufferIndex,
						count,
						ShaderDataTypeToGLBaseType(element.Type),
						element.Normalized ? GL_TRUE : GL_FALSE,
						layout.GetStride(),
						(const void*)(element.Offset + sizeof(float) * count * i));
					glVertexAttribDivisor(m_VertexBufferIndex, 1);
					m_VertexBufferIndex++;
				}
				break;
			}
			default:
				LNA_CORE_ASSERT(false, "Unknown ShaderDataType!");
			}
		}

        m_VertexBuffers.push_back(buffer);
    }

    void OpenGLVertexArray::SetIndexBuffer(Shared<IndexBuffer>& buffer)
    {
		LNA_PROFILE_FUNCTION();

        glBindVertexArray(m_RendererID);
        buffer->Bind();

        m_IndexBuffer = buffer;
    }
}