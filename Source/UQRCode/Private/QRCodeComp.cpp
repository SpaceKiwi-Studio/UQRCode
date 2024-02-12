// Copyright Space Kiwi Studio. All Rights Reserved.

#include "QRCodeComp.h"
#include "UQRCode/qrcodegen.hpp"

using qrcodegen::QrCode;

UQRCodeComp::UQRCodeComp()
{
	PrimaryComponentTick.bCanEverTick = false;
}

FColor UQRCodeComp::GetModulePixelColor(const QrCode& QrCode, const uint8 X, const uint8 Y)
{
	const FColor BlackColor = FColor::Black;
	const FColor WhiteColor = FColor::White;

	return QrCode.getModule(X, Y) ? WhiteColor : BlackColor;
}

UTexture2D* UQRCodeComp::GenerateQrCode(const QrCode& QrCode)
{
	const uint8 QrSize = QrCode.getSize();
	TArray<FColor> Pixels;
	Pixels.SetNumZeroed(QrSize * QrSize);

	for (uint8 x = 0; x < QrSize; ++x)
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

	// New code to set texture as no mipmap
	Texture->NeverStream = true;
	Texture->LODGroup = TEXTUREGROUP_Pixels2D;
	Texture->MipGenSettings = TMGS_NoMipmaps;
	Texture->Filter = TF_Nearest;

	Texture->UpdateResource();

	return Texture;
}

UTexture2D* UQRCodeComp::StringToQrCode(const FString& String, const EEcc Ecc)
{
	const QrCode QrCode = QrCode::encodeText(TCHAR_TO_UTF8(*String), MapEccEnumToQrEcc(Ecc));

	return GenerateQrCode(QrCode);
}

UTexture2D* UQRCodeComp::BinariesToQrCode(const TArray<uint8>& Data, const EEcc Ecc)
{
	const std::vector<uint8_t> BinaryData(Data.GetData(), Data.GetData() + Data.Num());

	const QrCode QrCode = QrCode::encodeBinary(BinaryData, MapEccEnumToQrEcc(Ecc));

	return GenerateQrCode(QrCode);
}
