#pragma once

#include "luna/renderer/Shader.h"

#include <glm/glm.hpp>

// TODO: Temporary Measure
typedef unsigned int GLenum;

namespace luna
{
	class OpenGLShader : public Shader
	{
	public:
		OpenGLShader(const std::string& filePath);
		OpenGLShader(const std::string& name, const std::string& vertSrc, const std::string& fragSrc);
		virtual ~OpenGLShader();

		virtual void Bind() const override;
		virtual void Unbind() const override;

		virtual void SetInt(const std::string& name, int value) override;
		virtual void SetIntArray(const std::string& name, int* values, uint32_t count) override;
		virtual void SetFloat(const std::string& name, float value) override;
		virtual void SetFloat2(const std::string& name, const glm::vec2& value) override;
		virtual void SetFloat3(const std::string& name, const glm::vec3& value) override;
		virtual void SetFloat4(const std::string& name, const glm::vec4& value) override;
		virtual void SetMat4(const std::string& name, const glm::mat4& value) override;

		virtual const std::string& GetName() const override { return m_Name; }

		void UploadUniformBool(const std::string& name, const bool value);

		void UploadUniform1i(const std::string& name, const int value); 
		void UploadUniform1iv(const std::string& name, const int* values, uint32_t count);
		void UploadUniform2i(const std::string& name, const glm::ivec2& value);
		void UploadUniform3i(const std::string& name, const glm::ivec3& value);
		void UploadUniform4i(const std::string& name, const glm::ivec4& value);

		void UploadUniform1f(const std::string& name, const float value);
		void UploadUniform2f(const std::string& name, const glm::vec2& value);
		void UploadUniform3f(const std::string& name, const glm::vec3& value);
		void UploadUniform4f(const std::string& name, const glm::vec4& value);

		void UploadUniformMat4(const std::string& name, const glm::mat4& value);
	private:
		std::string ReadFile(const std::string& filePath);
		std::unordered_map<GLenum, std::string> PreProcess(const std::string& source);
		void Compile(const std::unordered_map<GLenum, std::string>& shaderSrcs);
	private:
		uint32_t m_RendererID;
		std::string m_Name;
	};
}
