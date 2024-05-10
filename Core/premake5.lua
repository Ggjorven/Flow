project "Flow"
	kind "StaticLib"
	language "C++"
	cppdialect "C++20"
	staticruntime "On"

	architecture "x86_64"

	targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "flpch.h"
	pchsource "src/Flow/flpch.cpp"

	files
	{
		"src/Flow/*.h",
		"src/Flow/*.hpp",
		"src/Flow/*.cpp",

		"src/Flow/Core/**.h",
		"src/Flow/Core/**.hpp",
		"src/Flow/Core/**.cpp",

		"src/Flow/Utils/**.h",
		"src/Flow/Utils/**.hpp",
		"src/Flow/Utils/**.cpp"
	}

	defines
	{
		"_CRT_SECURE_NO_WARNINGS",
		"yaml_cpp_EXPORTS"
	}

	includedirs
	{
		"src",
		"src/Flow",

		"%{Dependencies.yaml_cpp.IncludeDir}"
	}

	links
	{
		"%{Dependencies.yaml_cpp.LibName}",
	}

	disablewarnings
	{
		"4005",
		"4996"
	}

	filter "system:windows"
		systemversion "latest"
		staticruntime "on"

		defines
		{
			"APP_PLATFORM_WINDOWS"
		}

	filter "system:linux"
		systemversion "latest"
		staticruntime "on"

		defines
		{
			"APP_PLATFORM_LINUX"
		}

	filter "configurations:Debug"
		defines "APP_DEBUG"
		runtime "Debug"
		symbols "on"
		editandcontinue "Off"

	filter "configurations:Release"
		defines "APP_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "APP_DIST"
		runtime "Release"
		optimize "Full"