// Copyright Space Kiwi Studio. All Rights Reserved.

using System.IO;
using UnrealBuildTool;

/**
 * @author https://github.com/SpaceKiwi-Studio
 * @copyright Space Kiwi Studio. All Rights Reserved.
 * @date 12/13/2023
 */
public class UQRCode : ModuleRules
{
	public UQRCode(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

		if (Target.Platform == UnrealTargetPlatform.Win64)
		{
			// Add Includes
			PublicSystemIncludePaths.Add(Path.Combine(PluginDirectory, "Source", "ThirdParty", "QR-Code-generator", "Includes"));
		}

		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
			}
			);
			
		
		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"CoreUObject",
				"Engine",
				"Slate",
				"SlateCore",
			}
			);
	}
}
