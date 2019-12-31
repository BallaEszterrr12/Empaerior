workspace "Empaerior"
	architecture "x64"
	 
	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}
outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{}"

project "Empaerior"
	location "Empaerior"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"
	
	

	
	targetdir("bin/" .. outputdir .. "/%{prj.name}")
	objdir("bin-int/" .. outputdir .. "/%{prj.name}")
	
	pchheader "pch.h"
	pchsource "%{prj.name}/src/pch.cpp"
	
	
	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}
	
	
	includedirs
	{
	"%{prj.name}/src",
	"../External Libraries/SDL2/include",
	"../External Libraries/SDL2_image/include",
	"../External Libraries/SDL2_mixer/include",
	"../External Libraries/SDL2_ttf/include"
	}
	libdirs 
	{ 
	"../External Libraries/SDL2/lib/x64",
	"../External Libraries/SDL2_image/lib/x64",
	"../External Libraries/SDL2_mixer/lib/x64",
	"../External Libraries/SDL2_ttf/lib/x64"
	}
	links 
	{ 
		"SDL2.lib",
		"SDL2main.lib",
		"SDL2_image.lib",
		"SDL2_ttf.lib",
		"SDL2_mixer.lib"
	}
	
	filter "system:windows"
		systemversion "latest"
	
	
	configuration "Debug"
         runtime "Debug"
		 symbols "on"

    configuration "Release"
         runtime "Debug"
         optimize "on"
		 
	configuration "Dist"
		runtime "Release"
		symbols "on"
	