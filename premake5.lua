workspace "Reme"
	architecture "x86_64"
	startproject "Sandbox"

	configurations
	{
		"Debug",
		"Release",
		"Dist",
		"Test",
	}

	flags
	{
		"MultiProcessorCompile"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include directories relative to root folder (solution directory)
IncludeDir = {}
IncludeDir["GLFW"] = "Reme/third_party/GLFW/include"
IncludeDir["glad"] = "Reme/third_party/glad/include"
IncludeDir["imgui"] = "Reme/third_party/imgui"
IncludeDir["glm"] = "Reme/third_party/glm"
IncludeDir["stb_image"] = "Reme/third_party/stb_image"
IncludeDir["lua"] = "Reme/third_party/lua/include"

group "Dependencies"
	include "Reme/third_party/GLFW"
	include "Reme/third_party/glad"
	include "Reme/third_party/imgui"
	include "Reme/third_party/lua"

group ""

project "Reme"
	location "Reme"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "RemePCH.h"
	pchsource "Reme/src/RemePCH.cpp"

	defines
	{
		"_CRT_SECURE_NO_WARNINGS"
	}

	files
	{
		"%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp",
        "%{prj.name}/third_party/stb_image/**.h",
		"%{prj.name}/third_party/stb_image/**.cpp",
		"%{prj.name}/third_party/glm/glm/**.hpp",
		"%{prj.name}/third_party/glm/glm/**.inl",
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/third_party/spdlog/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.glad}",
		"%{IncludeDir.imgui}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.stb_image}",
		"%{IncludeDir.lua}",
	}

	links
	{
		"GLFW",
		"glad",
		"imgui",
		"lua",
	}

	defines
	{
		"GLFW_INCLUDE_NONE"
	}

	filter "system:windows"
		systemversion "latest"
		links
		{
			"opengl32.lib",
		}

	filter "system:linux"
		links
		{
			"X11",
			"GL",
			"dl",
			"pthread",
			"m",
			"z",
			"Xext",
			"Xfixes",
		}

	filter "configurations:Debug"
		defines "DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "DIST"
		runtime "Release"
		optimize "on"

	filter "configurations:Test"
		defines "TEST"
		runtime "Debug"
		symbols "on"
		kind "ConsoleApp"

		defines
		{
			"TEST",
			"TEST_RENDERAPI",
		}

		files
		{
			"%{prj.name}/src/**.h",
			"%{prj.name}/src/**.cpp",
			"%{prj.name}/third_party/Catch2/**.hpp",
			"%{prj.name}/third_party/Catch2/**.cpp",
		}

		includedirs
		{
			"%{prj.name}/third_party/Catch2",
		}

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"Reme/third_party/spdlog/include",
		"Reme/src",
		"Reme/third_party",
		"%{IncludeDir.glm}",
		"%{IncludeDir.lua}",
	}

	links
	{
		"Reme",
		"lua",
	}

	filter "system:windows"
		systemversion "latest"

	-- On Linux the dependencies of the static library are not bundle together
	filter "system:linux"

		links
		{
			"GLFW",
			"glad",
			"imgui",
			"X11",
			"GL",
			"dl",
			"pthread",
			"m",
			"z",
			"Xext",
			"Xfixes",
		}

	filter "configurations:Debug"
		defines "_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "_DIST"
		runtime "Release"
		optimize "on"
