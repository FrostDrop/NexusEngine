outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "Sandbox"
	kind "ConsoleApp"
	language "C++"
	staticruntime "off"

	targetdir ("../Binaries/Bin/" .. outputdir)
	objdir ("../Binaries/Obj/" .. outputdir)

	files {
		"premake5.lua",
		"Source/**.h",
		"Source/**.cpp"
	}

	includedirs {
		"Source",

		"../Nexus/Source/**/Public",
		"../Nexus/Source/Core/**"
	}

	links {
		"Nexus"
	}

	filter "system:windows"
		cppdialect "C++17"
		systemversion "latest"

		defines {
			"NEXUS_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "NEXUS_DEBUG"
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		defines "NEXUS_RELEASE"
		runtime "Release"
		optimize "On"
	
	filter "configurations:Distribution"
		defines "NEXUS_DISTRIBUTION"
		runtime "Release"
		optimize "On"
		inlining "Auto"