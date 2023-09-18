workspace "LunarEngine"
    filename "Luna"
    architecture "x64"
    configurations { "Debug", "Release", "Distribution"}

    startproject "Lunar"

    OUTPUT_DIR = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "Lunar"
    location "Lunar"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++20"
    staticruntime "on"

    targetdir ("bin/" .. OUTPUT_DIR .. "/%{prj.name}")
    objdir ("bin-int/" .. OUTPUT_DIR .. "/%{prj.name}")

    files {
        "%{prj.name}/src/**.c",
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp",
        "%{prj.name}/src/**.hpp"
    }

    defines {
        "_CRT_SECURE_NO_WARNINGS"
    }

    filter "system:windows"
        systemversion "latest"
    
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