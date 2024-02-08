// Copyright Space Kiwi Studio. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "QRCodeComp.generated.h"

namespace qrcodegen
{
	class QrCode;
}

UCLASS(ClassGroup=(UQRCode), meta=(BlueprintSpawnableComponent))
class UQRCODE_API UQRCodeComp : public UActorComponent
{
	GENERATED_BODY()

public:
	UQRCodeComp();
	
	UFUNCTION(BlueprintCallable)
	UTexture2D* StringToQrCode(const FString& String);
	
private:
	static FColor GetModulePixelColor(const qrcodegen::QrCode& QrCode, uint8 x, uint8 y);
	static UTexture2D* GenerateQrCode(const qrcodegen::QrCode& QrCode);
};