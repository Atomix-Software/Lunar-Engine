workspace "LunarEngine"
    filename "Luna"
    architecture "x64"
    configurations { "Debug", "Release", "Distribution"}

    startproject "Lunar"

    OUTPUT_DIR = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

    INCLUDE_DIR = {}
    INCLUDE_DIR["GLFW"] = "Lunar/vendors/glfw/include"
    INCLUDE_DIR["GLM"]  = "Lunar/vendors/glm"
    INCLUDE_DIR["Glad"] = "Lunar/vendors/glad/include"
    INCLUDE_DIR["stb_image"] = "Lunar/vendors/stb_image"

    include "Lunar/vendors/glfw"
    include "Lunar/vendors/glad"

    project "Lunar"
        location "Lunar"
        kind "ConsoleApp"
        language "C++"
        cppdialect "C++20"
        staticruntime "on"

        targetdir ("bin/" .. OUTPUT_DIR .. "/%{prj.name}")
        objdir ("bin-int/" .. OUTPUT_DIR .. "/%{prj.name}")
        
        pchheader "luna/lnapch.h"
        pchsource "Lunar/src/luna/lnapch.cpp"

        files {
            "%{prj.name}/src/**.c",
            "%{prj.name}/src/**.h",
            "%{prj.name}/src/**.cpp",
            "%{prj.name}/src/**.hpp",

            "%{prj.name}/vendors/stb_image/**.cpp",
            "%{prj.name}/vendors/stb_image/**.h",

            "%{prj.name}/vendors/glm/glm/**.h",
            "%{prj.name}/vendors/glm/glm/**.hpp",
            "%{prj.name}/vendors/glm/glm/**.inl"
        }

        links {
            "glfw",
            "glad",
            "opengl32.lib"
        }

        defines {
            "_CRT_SECURE_NO_WARNINGS"
        }

        includedirs {
            "%{prj.name}/src",
            
            "%{INCLUDE_DIR.GLFW}",
            "%{INCLUDE_DIR.GLM}",
            "%{INCLUDE_DIR.Glad}",
            "%{INCLUDE_DIR.stb_image}"
        }

        filter "system:windows"
            systemversion "latest"

            defines {
                "LNA_PLATFORM_WINDOWS",
                "LNA_BUILD_DLL",
                "GLFW_INCLUDE_NONE"
            }

        filter "configurations:Debug" 
            defines "LNA_DEBUG" 
            runtime "Debug" 
            symbols "on"

        filter "configurations:Release" 
            defines "LNA_RELEASE" 
            runtime "Release" 
            symbols "on"

        filter "configurations:Distribution" 
            defines "LNA_DIST" 
            runtime "Release" 
            symbols "on"