------------------------------------------------------------------------------
-- Utilities
------------------------------------------------------------------------------
function FirstToUpper(str)
	return (str:gsub("^%l", string.upper))
end
------------------------------------------------------------------------------

------------------------------------------------------------------------------
-- Dependencies
------------------------------------------------------------------------------
Dependencies = 
{
	-- Libs
	yaml_cpp = 
	{
		LibName = "yaml-cpp",
		IncludeDir = "%{wks.location}/Core/vendor/yaml-cpp/include"
	},
	filewatch = 
	{
		IncludeDir = "%{wks.location}/Core/vendor/filewatch/include"
	}
}
------------------------------------------------------------------------------

------------------------------------------------------------------------------
-- Solution
------------------------------------------------------------------------------
outputdir = "%{cfg.buildcfg}-" .. FirstToUpper("%{cfg.system}")

workspace "Flow"
	architecture "x86_64"
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

group "Flow"
	include "Core"
group ""

include "Sandbox"
------------------------------------------------------------------------------