workspace "Cajo"
	architecture "x64"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include dirs relative to root dir (solution dir)
IncludeDir = {}
IncludeDir["GLFW"] = "Cajo/vendor/GLFW/include"
IncludeDir["Glad"] = "Cajo/vendor/Glad/include"
IncludeDir["ImGui"] = "Cajo/vendor/ImGui"

include "Cajo/vendor/GLFW"
include "Cajo/vendor/Glad"
include "Cajo/vendor/ImGui"

project "Cajo"
	location "Cajo"
	kind "SharedLib"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "cajopch.h"
	pchsource "Cajo/src/cajopch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGui}"
	}

	links
	{
		"GLFW",
		"Glad",
		"ImGui",
		"opengl32.lib"
	}

	filter "system:windows"
		cppdialect "c++17"
		staticruntime "Off"
		systemversion "latest"

		defines
		{
			"CAJO_PLATFORM_WINDOWS",
			"CAJO_BUILD_DLL",
			"GLFW_INCLUDE_NONE"
		}

		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
		}

	filter "configurations:Debug"
		defines "CAJO_DEBUG"
		symbols "On"
	
	filter "configurations:Release"
		defines "CAJO_RELEASE"
		optimize "On"

	filter "configurations:Dist"
		defines "CAJO_DIST"
		optimize "On"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
	}

	includedirs
	{
		"Cajo/vendor/spdlog/include",
		"Cajo/src"
	}

	filter "system:windows"
		cppdialect "c++17"
		staticruntime "Off"
		systemversion "latest"

		defines
		{
			"CAJO_PLATFORM_WINDOWS"
		}

		links
		{
			"Cajo"
		}

	filter "configurations:Debug"
		defines "CAJO_DEBUG"
		symbols "On"
	
	filter "configurations:Release"
		defines "CAJO_RELEASE"
		optimize "On"

	filter "configurations:Dist"
		defines "CAJO_DIST"
		optimize "On"