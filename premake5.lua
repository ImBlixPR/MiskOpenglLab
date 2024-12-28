workspace "MiskOpenglLab"
	
	architecture "x64"
	startproject "MiskOpenglLab"


	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}"

IncludeDir = {}
IncludeDir["GLFW"] = "MiskOpenglLab/vendor/GLFW/include"
IncludeDir["Glad"] = "MiskOpenglLab/vendor/Glad/include"
IncludeDir["imgui"] = "MiskOpenglLab/vendor/imgui"
IncludeDir["glm"] = "MiskOpenglLab/vendor/glm"
IncludeDir["stb"] = "MiskOpenglLab/vendor/STB/include"
IncludeDir["spdlog"] = "MiskOpenglLab/vendor/spdlog/include"

include "MiskOpenglLab/vendor/GLFW"
include "MiskOpenglLab/vendor/Glad"
include "MiskOpenglLab/vendor/imgui"

project "MiskOpenglLab"
	
	location "MiskOpenglLab"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "On"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "mkpch.h"
	pchsource "MiskOpenglLab/src/mkpch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"%{IncludeDir.spdlog}",
		"%{prj.name}/src",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.imgui}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.stb}"
	}

	links
	{
		"GLFW",
		"Glad",
		"imgui",
		"opengl32.lib"
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"GLFW_INCLUDE_NONE",
			"MK_ENABLE_ASSERTS"
		}


	filter "configurations:Debug"
		defines "MK_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "MK_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "MK_DIST"
		runtime "Release"
		optimize "on"
