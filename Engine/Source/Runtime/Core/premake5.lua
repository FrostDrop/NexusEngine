project "Core"
	kind "SharedLib"
	language "C++"
	staticruntime "off"

	targetname ("%{wks.name}-%{prj.name}")
	targetdir (BinaryOutputDirectory)
	objdir (IntermediateOutputDirectory)

	files {
		"premake5.lua",

		"Public/**.h",
		"Private/**.cpp"
	}

	includedirs {
		RuntimeSourceDirectory .. "**/Public",
	}

	filter "system:windows"
		cppdialect "C++17"
		systemversion "latest"

		defines {
			"NEXUS_PLATFORM_WINDOWS",
			"NEXUS_LIB_TYPE_DLL"
		}

	filter "system:linux"
		cppdialect "C++17"
		systemversion "latest"

		defines {
			"NEXUS_PLATFORM_LINUX"
		}

		links {
			os.findlib("X11")
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