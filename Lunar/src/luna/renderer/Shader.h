#pragma once

#include "luna/core/Core.h"

#include <string>
#include <unordered_map>
#include <glm/glm.hpp>

namespace luna
{
	class LNA_API Shader
	{
	public:
		Shader() = default;
		virtual ~Shader() = default;

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual void SetInt(const std::string& name, int value) = 0;
		virtual void SetIntArray(const std::string& name, int* values, uint32_t count) = 0;
		virtual void SetFloat(const std::string& name, float value) = 0;
		virtual void SetFloat2(const std::string& name, const glm::vec2& value) = 0;
		virtual void SetFloat4(const std::string& name, const glm::vec4& value) = 0;
		virtual void SetFloat3(const std::string& name, const glm::vec3& value) = 0;
		virtual void SetMat4(const std::string& name, const glm::mat4& value) = 0;

		virtual const std::string& GetName() const = 0;

		static Shared<Shader> Create(const std::string& filePath);
		static Shared<Shader> Create(const std::string& name, const std::string& vertPath, const std::string& fragPath);
	};

	class ShaderLibrary
	{
	public:
		void Add(const std::string& name, const Shared<Shader>& shader);
		void Add(const Shared<Shader>& shader);

		Shared<Shader> Load(const std::string& filepath);
		Shared<Shader> Load(const std::string& name, const std::string& filepath);

		Shared<Shader> Get(const std::string& name);

		bool Exists(const std::string& name) const;
	private:
		std::unordered_map<std::string, Shared<Shader>> m_Shaders;
	};
}