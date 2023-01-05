include "Dependencies.lua"

workspace "OpenGLTemplate"
	architecture "x86_64"
	startproject "OpenGLTemplate"
	
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

group "Dependencies"
	include "vendor/premake"
	include "OpenGLTemplate/vendor/GLFW"
	include "OpenGLTemplate/vendor/Glad"
	include "OpenGLTemplate/vendor/assimp"
group ""

include "OpenGLTemplate"