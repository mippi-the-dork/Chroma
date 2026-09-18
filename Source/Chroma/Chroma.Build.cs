// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
public class Chroma : ModuleRules
{
    public Chroma(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
        PublicDependencyModuleNames.AddRange(new[] { "Core", "CoreUObject", "Engine", "DeveloperSettings" });
        PrivateDependencyModuleNames.AddRange(new[] { "UnrealEd", "Slate", "SlateCore", "InputCore", "SceneOutliner", "LevelEditor", "AppFramework", "ApplicationCore", "Settings", "ToolMenus", "Projects", "RenderCore", "RHI" });
    }
}
