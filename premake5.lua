workspace "Empaerior"
	
	startproject "Application"
	configurations
	{
		"Debug32",
		"Release32",
		"Dist32",
		"Debug64",
		"Release64",
		"Dist64"
	}
   filter "configurations:*32"
      architecture "x86"

   filter "configurations:*64"
      architecture "x86_64"
	 
outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{}"

project "Empaerior"
	location "Empaerior"
	kind "StaticLib"
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
	
	defines
	{
		"_CRT_SECURE_NO_WARNINGS"
	}
	
	includedirs
	{
	"%{prj.name}/src",
	"External_Libraries/SDL/SDL2/include",
	"External_Libraries/SDL/SDL2_image/include",
	"External_Libraries/SDL/SDL2_mixer/include",
	"External_Libraries/SDL/SDL2_ttf/include",
	"External_Libraries/spdlog/include"
	}
	
	

	
	filter "system:windows"
		systemversion "latest"
		defines {"EMPAERIOR_WINDOWS"}

		
	filter "configurations:Debug*"
		defines "EMPAERIOR_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release*"
		defines "EMPAERIOR_RELEASE"
		runtime "Debug"
		optimize "on"

	filter "configurations:Dist*"
		defines "EMPAERIOR_DIST"
		runtime "Release"
		optimize "on"
	
	
project "Application"
	location "Application"
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
		
		"External_Libraries/SDL/SDL2/include",
		"External_Libraries/SDL/SDL2_image/include",
		"External_Libraries/SDL/SDL2_mixer/include",
		"External_Libraries/SDL/SDL2_ttf/include",
		"External_Libraries/spdlog/include",
		"Empaerior/Src"
	}

	links
	{
		"SDL2.lib",
		"SDL2main.lib",
		"SDL2_image.lib",
		"SDL2_ttf.lib",
		"SDL2_mixer.lib",
		"Empaerior"
	}
	
	filter "system:windows"
		systemversion "latest"
		defines {"EMPAERIOR_WINDOWS"}
		
	filter "configurations:Debug*"
		defines "EMPAERIOR_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release*"
		defines "EMPAERIOR_RELEASE"
		runtime "Debug"
		optimize "on"

	filter "configurations:Dist*"
		defines "EMPAERIOR_DIST"
		runtime "Release"
		optimize "on"
	
	
	filter "configurations:*32"
		libdirs 
		{ 
		"External_Libraries/SDL/SDL2/lib/x86",
		"External_Libraries/SDL/SDL2_image/lib/x86",
		"External_Libraries/SDL//SDL2_mixer/lib/x86",
		"External_Libraries/SDL/SDL2_ttf/lib/x86"
		}

   filter "configurations:*64"     
	libdirs 
	{ 
	"External_Libraries/SDL/SDL2/lib/x64",
	"External_Libraries/SDL/SDL2_image/lib/x64",
	"External_Libraries/SDL/SDL2_mixer/lib/x64",
	"External_Libraries/SDL/SDL2_ttf/lib/x64"
	}
	