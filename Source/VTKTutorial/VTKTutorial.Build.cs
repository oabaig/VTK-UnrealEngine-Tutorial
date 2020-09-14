// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.IO;

public class VTKTutorial : ModuleRules
{
	public VTKTutorial(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore" });

		PrivateDependencyModuleNames.AddRange(new string[] {  });

		// include header files
		PublicIncludePaths.Add(Path.Combine(ModuleDirectory, "include"));

		// include library files - Explicitly name each lib file
		PublicAdditionalLibraries.Add(Path.Combine(ModuleDirectory, "lib", "vtkCommonComputationalGeometry-9.0d.lib"));
		PublicAdditionalLibraries.Add(Path.Combine(ModuleDirectory, "lib", "vtkCommonCore-9.0d.lib"));
		PublicAdditionalLibraries.Add(Path.Combine(ModuleDirectory, "lib", "vtkCommonDataModel-9.0d.lib"));
		PublicAdditionalLibraries.Add(Path.Combine(ModuleDirectory, "lib", "vtkCommonExecutionModel-9.0d.lib"));
		PublicAdditionalLibraries.Add(Path.Combine(ModuleDirectory, "lib", "vtkCommonMath-9.0d.lib"));
		PublicAdditionalLibraries.Add(Path.Combine(ModuleDirectory, "lib", "vtkCommonMisc-9.0d.lib"));
		PublicAdditionalLibraries.Add(Path.Combine(ModuleDirectory, "lib", "vtkCommonSystem-9.0d.lib"));
		PublicAdditionalLibraries.Add(Path.Combine(ModuleDirectory, "lib", "vtkCommonTransforms-9.0d.lib"));
		PublicAdditionalLibraries.Add(Path.Combine(ModuleDirectory, "lib", "vtkFiltersCore-9.0d.lib"));
		PublicAdditionalLibraries.Add(Path.Combine(ModuleDirectory, "lib", "vtkFiltersGeneral-9.0d.lib"));
		PublicAdditionalLibraries.Add(Path.Combine(ModuleDirectory, "lib", "vtkFiltersSources-9.0d.lib"));


		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
