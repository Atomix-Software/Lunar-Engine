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
    INCLUDE_DIR["entt"] = "Lunar/vendors/entt/include"
    INCLUDE_DIR["stb"] = "Lunar/vendors/stb"
    INCLUDE_DIR["libogg"] = "Lunar/vendors/libogg/include"
    INCLUDE_DIR["libvorbis"] = "Lunar/vendors/libvorbis/include"
    INCLUDE_DIR["openal"] = "Lunar/vendors/openal-soft/include"
    INCLUDE_DIR["freetype"] = "Lunar/vendors/freetype/include"
    INCLUDE_DIR["spdlog"] = "Lunar/vendors/spdlog/include"

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

            "%{prj.name}/vendors/stb/**.cpp",
            "%{prj.name}/vendors/stb/**.h",

            "%{prj.name}/vendors/glm/glm/**.h",
            "%{prj.name}/vendors/glm/glm/**.hpp",
            "%{prj.name}/vendors/glm/glm/**.inl"
        }

        defines {
            "_CRT_SECURE_NO_WARNINGS",
            "AL_LIBTYPE_STATIC"
        }

        includedirs {
            "%{prj.name}/src",
            
            "%{INCLUDE_DIR.GLFW}",
            "%{INCLUDE_DIR.GLM}",
            "%{INCLUDE_DIR.Glad}",
            "%{INCLUDE_DIR.entt}",
            "%{INCLUDE_DIR.libvorbis}",
            "%{INCLUDE_DIR.libogg}",
            "%{INCLUDE_DIR.openal}",
            "%{INCLUDE_DIR.freetype}",
            "%{INCLUDE_DIR.spdlog}",
            "%{INCLUDE_DIR.stb}"
        }

        links {
            "glfw",
            "glad",
            "opengl32.lib",
            "./Lunar/vendors/freetype/libs/freetype.lib",
            "./Lunar/vendors/libogg/libs/ogg.lib",
            "./Lunar/vendors/libvorbis/libs/vorbis.lib",
            "./Lunar/vendors/libvorbis/libs/vorbisenc.lib",
            "./Lunar/vendors/libvorbis/libs/vorbisfile.lib",
            "./Lunar/vendors/openal-soft/libs/alcommon.lib",
            "./Lunar/vendors/openal-soft/libs/al-excommon.lib",
            "./Lunar/vendors/openal-soft/libs/OpenAL32.lib",
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
            "%{INCLUDE_DIR.entt}",
            "%{INCLUDE_DIR.libvorbis}",
            "%{INCLUDE_DIR.libogg}",
            "%{INCLUDE_DIR.openal}",
            "%{INCLUDE_DIR.stb}",
            "%{INCLUDE_DIR.freetype}",
            "%{INCLUDE_DIR.spdlog}",
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