workspace "Cajo"
	architecture "x64"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "Cajo"
	location "Cajo"
	kind "SharedLib"
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
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include"
	}

	filter "system:windows"
		cppdialect "c++17"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"CAJO_PLATFORM_WINDOWS",
			"CAJO_BUILD_DLL"
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
		symbols "On"

	filter "configurations:Dist"
		defines "CAJO_DIST"
		symbols "On"

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
		staticruntime "On"
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
		symbols "On"

	filter "configurations:Dist"
		defines "CAJO_DIST"
		symbols "On"