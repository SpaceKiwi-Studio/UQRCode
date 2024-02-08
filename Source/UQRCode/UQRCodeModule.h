// Copyright Space Kiwi Studio. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include ""
#include "Modules/ModuleManager.h"

class FUQRCodeModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};
