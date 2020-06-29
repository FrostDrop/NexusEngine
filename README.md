# Nexus Engine

Welcome to the Nexus Engine source code!

## Status

| System | Build Status (master) | Build Status (development) |
| --- | --- | --- |
| Windows | [![Build Status](https://dev.azure.com/FrostDrop/NexusEngine/_apis/build/status/FrostDrop.NexusEngine?branchName=master&jobName=Windows)](https://dev.azure.com/FrostDrop/NexusEngine/_build/latest?definitionId=1&branchName=master) | [![Build Status](https://dev.azure.com/FrostDrop/NexusEngine/_apis/build/status/FrostDrop.NexusEngine?branchName=development&jobName=Windows)](https://dev.azure.com/FrostDrop/NexusEngine/_build/latest?definitionId=1&branchName=development) |
| Linux | [![Build Status](https://dev.azure.com/FrostDrop/NexusEngine/_apis/build/status/FrostDrop.NexusEngine?branchName=masterjobName=Linux)](https://dev.azure.com/FrostDrop/NexusEngine/_build/latest?definitionId=1&branchName=master) | [![Build Status](https://dev.azure.com/FrostDrop/NexusEngine/_apis/build/status/FrostDrop.NexusEngine?branchName=development&jobName=Windows)](https://dev.azure.com/FrostDrop/NexusEngine/_build/latest?definitionId=1&branchName=development) |
| Mac | [![Build Status](https://dev.azure.com/FrostDrop/NexusEngine/_apis/build/status/FrostDrop.NexusEngine?branchName=masterjobName=Mac)](https://dev.azure.com/FrostDrop/NexusEngine/_build/latest?definitionId=1&branchName=master) | [![Build Status](https://dev.azure.com/FrostDrop/NexusEngine/_apis/build/status/FrostDrop.NexusEngine?branchName=development&jobName=Windows)](https://dev.azure.com/FrostDrop/NexusEngine/_build/latest?definitionId=1&branchName=development) |

## Getting started

### Windows

1. **Clone** the repository. We recommend the master branch, as it is the most stable one.
2. Install **Visual Studio 2019**. All versions of Visual Studio 2019 should be able to build the Nexus Engine. Make sure you select the "Desktop development with C++" workload.
3. Head over to the project directory and run the **Setup.bat** file.
4. Run the **GenerateProjectFiles.bat** file. This will generate the Visual Studio solution files.
5. Open the **Nexus.sln** file with Visual Studio. Select the **Distribution** configuration and build the project. Note, at the time the Nexus Engine only compiles for **64-Bit** systems.
6. If the compilation finished, hit **F5** to run the Nexus Engine.

### MacOS

1. **Clone** the repository. We recommend the master branch, as it is the most stable one.
2. Install the latest version of **Xcode**.
3. Head over to the project directory and run the **Setup.command** file.
4. Run the **GenerateProjectFiles.command** file. This will generate the Xcode project files.
5. Open the **Nexus.xcworkspace** file with Xcode. Select the **Distribution** configuration and build the project. Note, at the time the Nexus Engine only compiles for **64-Bit** systems.
6. If the compilation finished, hit **Product -> Run** to run the Nexus Engine.

### Linux

1. **Clone** the repository. We recommend the master branch, as it is the most stable one.
2. Make sure **GNU Make** is installed.
3. Head over to the project directory and run the **Setup.sh** file.
4. Run the **GenerateProjectFiles.sh** file. This will generate the project Makefiles.
5. Open the **Terminal** within the project directory and run **make**.
6. If the compilation finished, head over to the **binary directory** (Engine/Binaries/Debug-[os-name]-x86_64/), open the terminal and run **./Nexus-Sandbox**.
