// Fill out your copyright notice in the Description page of Project Settings.


#include "ServicesBF.h"

FString UServicesBF::GetMD5Sum(FString InputText)
{
	return FMD5::HashAnsiString(*InputText);
}

FString UServicesBF::GenerateToken()
{
	FString alhabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";//52
	FString result;
	TArray<TCHAR> symbol = alhabet.GetCharArray();
	TCHAR CharSymbol;
	int v2;
	for (int i = 0; i < 4; i++)
	{
		v2 = rand() % 52;
		CharSymbol = symbol[v2];
		result.AppendChar(CharSymbol);

		v2 = rand() % 52;
		CharSymbol = symbol[v2];
		result.AppendChar(CharSymbol);

		v2 = rand() % 10;
		result.AppendInt(v2);
	}
	return result;
}

FString UServicesBF::Encrypt(FString InputString, FString Key)
{
	// Check inputs
	if (InputString.IsEmpty()) return "";  //empty string? do nothing
	if (Key.IsEmpty()) return "";

	// To split correctly final result of decryption from trash symbols
	FString SplitSymbol = "EL@$@!";
	InputString.Append(SplitSymbol);

	// We need at least 32 symbols key
	Key = FMD5::HashAnsiString(*Key);
	TCHAR* KeyTChar = Key.GetCharArray().GetData();
	ANSICHAR* KeyAnsi = (ANSICHAR*)TCHAR_TO_ANSI(KeyTChar);

	// Calculate blob size and create blob
	uint8* Blob;
	uint32 Size;

	Size = InputString.Len();
	Size = Size + (FAES::AESBlockSize - (Size % FAES::AESBlockSize));

	Blob = new uint8[Size];

	// Convert string to bytes and encrypt
	if (StringToBytes(InputString, Blob, Size)) {

		FAES::EncryptData(Blob, Size, KeyAnsi);
		InputString = FString::FromHexBlob(Blob, Size);

		delete Blob;
		return InputString;
	}

	delete Blob;
	return "";
}

FString UServicesBF::Decrypt(FString InputString, FString Key)
{
	// Check inputs
	if (InputString.IsEmpty()) return "";
	if (Key.IsEmpty()) return "";

	// To split correctly final result of decryption from trash symbols
	FString SplitSymbol = "EL@$@!";

	// We need at least 32 symbols key
	Key = FMD5::HashAnsiString(*Key);
	TCHAR* KeyTChar = Key.GetCharArray().GetData();
	ANSICHAR* KeyAnsi = (ANSICHAR*)TCHAR_TO_ANSI(KeyTChar);

	// Calculate blob size and create blob
	uint8* Blob;
	uint32 Size;

	Size = InputString.Len();
	Size = Size + (FAES::AESBlockSize - (Size % FAES::AESBlockSize));

	Blob = new uint8[Size];

	// Convert string to bytes and decrypt
	if (FString::ToHexBlob(InputString, Blob, Size)) {

		FAES::DecryptData(Blob, Size, KeyAnsi);
		InputString = BytesToString(Blob, Size);

		// Split required data from trash
		FString LeftData;
		FString RightData;
		InputString.Split(SplitSymbol, &LeftData, &RightData, ESearchCase::CaseSensitive, ESearchDir::FromStart);
		InputString = LeftData;

		delete Blob;
		return InputString;
	}

	delete Blob;
	return "";
}