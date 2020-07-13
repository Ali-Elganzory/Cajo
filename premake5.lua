workspace "Cajo"
	architecture "x64"
	startproject "Sandbox"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

	flags
	{
		"MultiProcessorCompile"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include dirs relative to root dir (solution dir)
IncludeDir = {}
IncludeDir["GLFW"] = "Cajo/vendor/GLFW/include"
IncludeDir["Glad"] = "Cajo/vendor/Glad/include"
IncludeDir["ImGui"] = "Cajo/vendor/ImGui"
IncludeDir["glm"] = "Cajo/vendor/glm"
IncludeDir["stb_image"] = "Cajo/vendor/stb_image"

include "Cajo/vendor/GLFW"
include "Cajo/vendor/Glad"
include "Cajo/vendor/ImGui"

project "Cajo"
	location "Cajo"
	kind "StaticLib"
	language "C++"
	cppdialect "c++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "cajopch.h"
	pchsource "Cajo/src/cajopch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/vendor/stb_image/**.h",
		"%{prj.name}/vendor/stb_image/**.cpp",
		"%{prj.name}/vendor/glm/glm/**.hpp",
		"%{prj.name}/vendor/glm/glm/**.inl",
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.stb_image}",
	}

	links
	{
		"GLFW",
		"Glad",
		"ImGui",
		"opengl32.lib"
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"CAJO_PLATFORM_WINDOWS",
			"CAJO_BUILD_DLL",
			"GLFW_INCLUDE_NONE"
		}

	filter "configurations:Debug"
		defines "CAJO_DEBUG"
		runtime "Debug"
		symbols "on"
	
	filter "configurations:Release"
		defines "CAJO_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "CAJO_DIST"
		runtime "Release"
		optimize "on"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	cppdialect "c++17"
	staticruntime "on"

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
		"Cajo/src",
		"Cajo/vendor",
		"%{IncludeDir.glm}"
	}

	filter "system:windows"
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
		runtime "Debug"
		symbols "on"
	
	filter "configurations:Release"
		defines "CAJO_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "CAJO_DIST"
		runtime "Release"
		optimize "on"
		