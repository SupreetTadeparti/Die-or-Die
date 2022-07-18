workspace "Moon"
	architecture "x64"

	configurations
	{
		"Debug",
		"Release",
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "Moon"
	location "Moon"
	kind "SharedLib"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.hpp",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"Moon/vendor",
		"Moon/vendor/GLFW/include",
		"Moon/vendor/GL/include",
		"Moon/vendor/freetype/include"
	}

	libdirs
	{
		"Moon/vendor/GLFW/lib",
		"Moon/vendor/GL/lib",
		"Moon/vendor/freetype/lib"
	}

	links
	{
		"glew32s",
		"opengl32",
		"glfw3",
		"freetype"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"MOON_PLATFORM_WINDOWS",
			"MOON_BUILD_DLL",
			"GLEW_STATIC"
		}

		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
		}

	filter "configurations:Debug"
		defines "MOON_DEBUG"
		symbols "On"
		staticruntime "off"
		runtime "Debug"

	filter "configurations:Release"
		defines "MOON_RELEASE"
		optimize "On"
		staticruntime "off"
		runtime "Release"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.hpp",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"Moon/vendor",
		"Moon/vendor/GLFW/include",
		"Moon/vendor/GL/include",
		"Moon/vendor/freetype/include",
		"Moon/src",
	}

	links
	{
		"Moon"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"MOON_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "MOON_DEBUG"
		symbols "On"
		staticruntime "off"
		runtime "Debug"

	filter "configurations:Release"
		defines "MOON_RELEASE"
		optimize "On"
		staticruntime "off"
		runtime "Release"