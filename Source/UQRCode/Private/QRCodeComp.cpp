// Copyright Space Kiwi Studio. All Rights Reserved.

#include "QRCodeComp.h"
#include "UQRCode//qrcodegen.hpp"

using qrcodegen::QrCode;

UQRCodeComp::UQRCodeComp()
{
	PrimaryComponentTick.bCanEverTick = false;
}

FColor UQRCodeComp::GetModulePixelColor(const qrcodegen::QrCode& QrCode, uint8 x, uint8 y)
{
	const FColor BlackColor = FColor::Black;
	const FColor WhiteColor = FColor::White;
	
	return QrCode.getModule(x, y) ? WhiteColor : BlackColor;
}

UTexture2D* UQRCodeComp::GenerateQrCode(const qrcodegen::QrCode& QrCode)
{
	const uint8 QrSize = QrCode.getSize();
	TArray<FColor> Pixels;
	Pixels.SetNumZeroed(QrSize * QrSize);
	
	for (uint8 x =0; x < QrSize; ++x)
	{
		for (uint8 y = 0; y < QrSize; ++y)
		{
			Pixels[x + y * QrSize] = GetModulePixelColor(QrCode, x, y);
		}
	}
	
	UTexture2D* Texture = UTexture2D::CreateTransient(QrSize, QrSize, PF_B8G8R8A8, "QRCode");
	void* Data = Texture->GetPlatformData()->Mips[0].BulkData.Lock(LOCK_READ_ONLY);
	FMemory::Memcpy(Data, Pixels.GetData(), QrSize * QrSize * 4);
	Texture->GetPlatformData()->Mips[0].BulkData.Unlock();
	Texture->UpdateResource();
	Texture->Filter = TF_Nearest;
	
	return Texture;
}

UTexture2D* UQRCodeComp::StringToQrCode(const FString& String)
{
	const qrcodegen::QrCode QrCode = qrcodegen::QrCode::encodeText(TCHAR_TO_UTF8(*String), qrcodegen::QrCode::Ecc::LOW);
	
	return GenerateQrCode(QrCode);
}
