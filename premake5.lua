workspace "Reme"
	architecture "x86_64"
	startproject "Sandbox2D"

	configurations
	{
		"Debug",
		"Release",
		"Dist",
	}

	flags
	{
		"MultiProcessorCompile"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include directories relative to root folder (solution directory)
IncludeDir = {}
IncludeDir["GLFW"] = "Reme/vendor/GLFW/include"
IncludeDir["glad"] = "Reme/vendor/glad/include"
IncludeDir["imgui"] = "Reme/vendor/imgui"
IncludeDir["glm"] = "Reme/vendor/glm"
IncludeDir["stb_image"] = "Reme/vendor/stb_image"
IncludeDir["lua"] = "Reme/vendor/lua/include"

group "Dependencies"
	include "Reme/vendor/GLFW"
	include "Reme/vendor/glad"
	include "Reme/vendor/imgui"

group ""

project "Reme"
	location "Reme"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "pch.h"
	pchsource "Reme/src/pch.cpp"

	defines
	{
		"_CRT_SECURE_NO_WARNINGS"
	}

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
		"%{IncludeDir.glad}",
		"%{IncludeDir.imgui}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.stb_image}",
		"%{IncludeDir.lua}",
	}

	libdirs
	{
		"Reme/vendor/lua/"
	}

	links
	{
		"GLFW",
		"glad",
		"imgui",
		"lua53:static",
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

project "Sandbox2D"
	location "Sandbox2D"
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
		"Reme/vendor/spdlog/include",
		"Reme/src",
		"Reme/vendor",
		"%{IncludeDir.glm}",
		"%{IncludeDir.lua}",
	}

	links
	{
		"Reme"
	}

	filter "system:windows"
		systemversion "latest"

	-- On Linux the dependencies of the static library are not bundle together
	filter "system:linux"
		libdirs
		{
			"Reme/vendor/lua/"
		}

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
			"lua53:static",
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
