outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "Nexus"
	kind "SharedLib"
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
		"Source/**/Public",
		"Source/Core/**"
	}

	filter "system:windows"
		cppdialect "C++17"
		systemversion "latest"

		links {
			"OpenGL32"
		}

		defines {
			"NEXUS_PLATFORM_WINDOWS",
			"NEXUS_LIB_TYPE_DLL"
		}

	filter "system:not windows"

		links {
			"GL"
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