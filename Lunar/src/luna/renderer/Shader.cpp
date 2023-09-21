#include <lnapch.h>
#include "Shader.h"

#include "Renderer.h"

#include "platform/opengl/OpenGLShader.h"

namespace luna
{
    Shared<Shader> Shader::Create(const std::string& filePath)
    {
        switch (Renderer::GetAPI())
        {
            case RendererAPI::API::None:   LNA_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
            case RendererAPI::API::OpenGL: return CreateShared<OpenGLShader>(filePath);
        }

        LNA_CORE_ASSERT(false, "Unknown Rendering API!");
        return nullptr;
    }

	Shared<Shader> Shader::Create(const std::string& name, const std::string& vertPath, const std::string& fragPath)
	{
        switch (Renderer::GetAPI())
        {
            case RendererAPI::API::None:   LNA_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
            case RendererAPI::API::OpenGL: return CreateShared<OpenGLShader>(name, vertPath, fragPath);
        }

        LNA_CORE_ASSERT(false, "Unknown Rendering API!");
        return nullptr;
	}

    void ShaderLibrary::Add(const std::string& name, const Shared<Shader>& shader)
    {
        LNA_CORE_ASSERT(!Exists(name), "Shader already exists!");
        m_Shaders[name] = shader;
    }

    void ShaderLibrary::Add(const Shared<Shader>& shader)
    {
        auto& name = shader->GetName();
        Add(name, shader);
    }

    Shared<Shader> ShaderLibrary::Load(const std::string& filepath)
    {
        auto shader = Shader::Create(filepath);
        Add(shader);
        return shader;
    }

    Shared<Shader> ShaderLibrary::Load(const std::string& name, const std::string& filepath)
    {
        auto shader = Shader::Create(filepath);
        Add(name, shader);
        return shader;
    }

    Shared<Shader> ShaderLibrary::Get(const std::string& name)
    {
        LNA_CORE_ASSERT(Exists(name), "Shader not found!");
        return m_Shaders[name];
    }
    
    bool ShaderLibrary::Exists(const std::string& name) const
    {
        return m_Shaders.find(name) != m_Shaders.end();
    }
}