// Copyright Epic Games, Inc. All Rights Reserved.

using System;
using System.IO;
using UnrealBuildTool;

public class GDAL : ModuleRules
{
	public GDAL(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
		string BasePath = Path.Combine(ModuleDirectory, "../../ThirdParty2");
		bEnableUndefinedIdentifierWarnings = false;
		CppStandard = CppStandardVersion.Cpp17;
		bUseRTTI = true;
		bEnableExceptions = true;

		if (Target.Platform == UnrealTargetPlatform.Win64)
		{
			PublicIncludePaths.Add(Path.Combine(BasePath, "include"));
			string StaticLibraryPaths = Path.Combine(BasePath, "lib");
			string[] StaticLibraries = Directory.GetFiles(StaticLibraryPaths, "*.lib");
			foreach (string StaticLibrary in StaticLibraries)
			{
				Console.WriteLine(StaticLibrary);
				PublicAdditionalLibraries.Add(StaticLibrary);
			}
			
			string LibraryPaths = Path.Combine(BasePath, "bin");
			PublicRuntimeLibraryPaths.Add(LibraryPaths);
			string[] Libraries = Directory.GetFiles(LibraryPaths,  "*.dll");
			foreach (string LibraryPath in Libraries)
			{
				string LibraryName = Path.GetFileName(LibraryPath);
				Console.WriteLine(LibraryPath);
				RuntimeDependencies.Add(LibraryPath);
				RuntimeDependencies.Add(Path.Combine("$(TargetOutputDir)/", LibraryName), LibraryPath);
				RuntimeDependencies.Add(Path.Combine("$(BinaryOutputDir)/", LibraryName), LibraryPath);
			}
			
			PublicDependencyModuleNames.AddRange(new string[]
			{
				"Core",
				"CoreUObject",
				"Engine",
			});
		}
		else
		{
			Console.Error.WriteLine("Only support Win64 Platform");
		}
	}
}