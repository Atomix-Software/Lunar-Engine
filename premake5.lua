workspace "LunarEngine"
    filename "Luna"
    architecture "x64"
    configurations { "Debug", "Release", "Distribution"}

    startproject "Apollo"

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
        kind "StaticLib"
        language "C++"
        cppdialect "C++20"
        staticruntime "on"

        targetdir ("bin/" .. OUTPUT_DIR .. "/%{prj.name}")
        objdir ("bin-int/" .. OUTPUT_DIR .. "/%{prj.name}")
        
        pchheader "lnapch.h"
        pchsource "Lunar/src/lnapch.cpp"

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

        defines {
            "_CRT_SECURE_NO_WARNINGS"
        }

        includedirs {
            "%{prj.name}/src",
            "%{prj.name}/vendors/spdlog/include",
            
            "%{INCLUDE_DIR.GLFW}",
            "%{INCLUDE_DIR.GLM}",
            "%{INCLUDE_DIR.Glad}",
            "%{INCLUDE_DIR.stb_image}"
        }

        links {
            "glfw",
            "glad",
            "opengl32.lib"
        }

        filter "system:windows"
            systemversion "latest"

            defines {
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

project "Apollo"
        location "Apollo" 
        kind "ConsoleApp" 
        language "C++" 
        cppdialect "C++20"
        staticruntime "on" 
        
        targetdir("bin/" .. OUTPUT_DIR .. "/%{prj.name}")
        objdir("bin-int/" .. OUTPUT_DIR .. "/%{prj.name}")

        files {
            "%{prj.name}/src/**.h",
            "%{prj.name}/src/**.c",
            "%{prj.name}/src/**.hpp",
            "%{prj.name}/src/**.cpp"
	    }

        includedirs
        {
            "%{INCLUDE_DIR.GLM}",
            "Lunar/vendors/spdlog/include",
            "Lunar/vendors",
            "Lunar/src"
        }

        links
        {
            "Lunar"
        }

        filter "system:windows"
            staticruntime "On"
            systemversion "latest"

        filter "configurations:Debug"
            defines "LNA_DEBUG"
            runtime "Debug"
            symbols "on"

        filter "configurations:Release"
            defines "LNA_RELEASE"
            runtime "Release"
            optimize "on"

        filter "configurations:Dist"
            defines "LNA_DIST"
            runtime "Release"
            optimize "on"