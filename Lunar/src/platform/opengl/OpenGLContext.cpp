#include <lnapch.h>

#include "OpenGLContext.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace luna
{
	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle) : 
		m_WindowHandle(windowHandle) 
	{
		LNA_CORE_ASSERT(windowHandle, "Couldn't find an OpenGL Context!");
	}

	void OpenGLContext::Init()
	{
		LNA_PROFILE_FUNCTION();
		glfwMakeContextCurrent(m_WindowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		LNA_CORE_ASSERT(status, "Failed to initialize GLAD!");

		LNA_CORE_INFO("OpenGL Info:");
		LNA_CORE_INFO("  Vendor: {0}", (const char*) glGetString(GL_VENDOR));
		LNA_CORE_INFO("  Renderer: {0}", (const char*)glGetString(GL_RENDERER));
		LNA_CORE_INFO("  Version: {0}", (const char*)glGetString(GL_VERSION));

	#ifdef LNA_ENABLE_ASSERT
		int major, minor;
		glGetIntegerv(GL_MAJOR_VERSION, &major);
		glGetIntegerv(GL_MINOR_VERSION, &minor);

		LNA_CORE_ASSERT(major > 4 || (major == 4 && minor >= 5), "Arcane Engine requires OpenGL 4.5 or higher!");
	#endif
	}

	void OpenGLContext::SwapBuffers()
	{
		LNA_PROFILE_FUNCTION();
		glfwSwapBuffers(m_WindowHandle);
	}
}