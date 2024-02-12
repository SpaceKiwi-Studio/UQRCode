// Copyright Space Kiwi Studio. All Rights Reserved.

#pragma once

#include <vector>

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "UQRCode/qrcodegen.hpp"
#include "QRCodeComp.generated.h"

class IHttpRequest;

namespace qrcodegen
{
	class QrCode;
}

UENUM(BlueprintType)
enum class EEcc : uint8
{
	Ecc_Low = 0,
	Ecc_Medium = 1,
	Ecc_Quartile = 2,
	Ecc_High = 3
};

UCLASS(ClassGroup=(UQRCode), meta=(BlueprintSpawnableComponent))
class UQRCODE_API UQRCodeComp : public UActorComponent
{
	GENERATED_BODY()

public:
	UQRCodeComp();

	UFUNCTION(BlueprintCallable, Category = "QRCode")
	static TArray<uint8> CreateTextFileAndReturnBinaryData(const FString& Data, const FString& FileName,
	                                                       FString& FullFilePath)
	{
		const TCHAR* TempDir = FPlatformProcess::UserTempDir();
		const int64 CurrentTime = FDateTime::UtcNow().ToUnixTimestamp();
		const FString FormattedFileName = FString::Printf(TEXT("%lld_%s.txt"), CurrentTime, *FileName);
		FullFilePath = FString::Printf(TEXT("%s%s"), TempDir, *FormattedFileName);

		// Create .txt file from FString
		FFileHelper::SaveStringToFile(Data, *FullFilePath);

		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FullFilePath);

		// Read the file back into a TArray<uint8>
		TArray<uint8> BinaryData;
		FFileHelper::LoadFileToArray(BinaryData, *FileName);

		return BinaryData;
	}

	UFUNCTION(BlueprintCallable, Category = "QRCode")
	static UTexture2D* StringToQrCode(const FString& String, const EEcc Ecc);

	UFUNCTION(BlueprintCallable, Category = "QRCode")
	static UTexture2D* BinariesToQrCode(const TArray<uint8>& Data, EEcc Ecc);

private:
	static FColor GetModulePixelColor(const qrcodegen::QrCode& QrCode, uint8 X, uint8 Y);
	static UTexture2D* GenerateQrCode(const qrcodegen::QrCode& QrCode);

	static qrcodegen::QrCode::Ecc MapEccEnumToQrEcc(const EEcc Ecc)
	{
		switch (Ecc)
		{
		case EEcc::Ecc_Low:
			return qrcodegen::QrCode::Ecc::LOW;
		case EEcc::Ecc_Medium:
			return qrcodegen::QrCode::Ecc::MEDIUM;
		case EEcc::Ecc_Quartile:
			return qrcodegen::QrCode::Ecc::QUARTILE;
		case EEcc::Ecc_High:
			return qrcodegen::QrCode::Ecc::HIGH;
		default:
			return qrcodegen::QrCode::Ecc::LOW;
		}
	}
};
