ProjectName = "Nexus"

EngineDirectory = path.getabsolute("Engine/") .. "/"
SampleDirectory = path.getabsolute("Samples/") .. "/"
TemplateDirectory = path.getabsolute("Templates/") .. "/"


BinaryDirectory = EngineDirectory .. "Binaries/"
IntermediateDirectory = EngineDirectory .. "Intermediates/"

BuildDirectory = EngineDirectory .. "Build/"

SourceDirectory = EngineDirectory .. "Source/"
ShaderDirectory = EngineDirectory .. "Shaders/"

OutputDirectory = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}/"
BinaryOutputDirectory = BinaryDirectory .. OutputDirectory
IntermediateOutputDirectory = IntermediateDirectory .. OutputDirectory


workspace "Nexus"
	architecture "x64"
	startproject "Sandbox"

	configurations {
		"Debug",
		"Release",
		"Distribution"
	}

include (SourceDirectory .. "Core")
include (SourceDirectory .. "Sandbox")