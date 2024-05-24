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
		IncludeDir = "%{wks.location}/vendor/yaml-cpp/include"
	},
	filewatch = 
	{
		IncludeDir = "%{wks.location}/vendor/filewatch/include"
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

group "Dependencies"
	include "vendor/yaml-cpp"
group ""

group "Flow"
	include "Core"
group ""

include "Sandbox"
------------------------------------------------------------------------------