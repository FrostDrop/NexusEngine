EngineDirectory = path.getabsolute("Engine/") .. "/"
SampleDirectory = path.getabsolute("Samples/") .. "/"
TemplateDirectory = path.getabsolute("Templates/") .. "/"

BuildDirectory = EngineDirectory .. "Build/"
BinaryDirectory = EngineDirectory .. "Binaries/"
IntermediateDirectory = EngineDirectory .. "Intermediates/"

SourceDirectory = EngineDirectory .. "Source/"
ShaderDirectory = EngineDirectory .. "Shaders/"

RuntimeSourceDirectory = SourceDirectory .. "Runtime/"
ThirdPartySourceDirectory = SourceDirectory .. "ThirdParty/"

OutputDirectoryName = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}/"
BinaryOutputDirectory = BinaryDirectory .. OutputDirectoryName
IntermediateOutputDirectory = IntermediateDirectory .. OutputDirectoryName


workspace "Nexus"
	architecture "x64"
	startproject "Sandbox"

	configurations {
		"Debug",
		"Release",
		"Distribution"
	}

include (RuntimeSourceDirectory .. "Core")
include (RuntimeSourceDirectory .. "Sandbox")