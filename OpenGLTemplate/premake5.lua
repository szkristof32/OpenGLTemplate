project "OpenGLTemplate"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "off"
	
	targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")
	
	files
	{
		"src/**.cpp",
		"src/**.h"
	}
	
	defines
	{
		"GLFW_INCLUDE_NONE"
	}
	
	includedirs
	{
		"src",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.spdlog}",
		"%{IncludeDir.assimp}"
	}
	
	links
	{
		"GLFW",
		"Glad",
		"opengl32.lib"
	}
	
	filter "system:windows"
		systemversion "latest"
		
		defines
		{
			"PLATFORM_WINDOWS",
			"BUILD_DLL"
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