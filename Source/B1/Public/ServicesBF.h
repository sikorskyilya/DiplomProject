// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "ServicesBF.generated.h"

/**
 * 
 */
UCLASS()
class B1_API UServicesBF : public UBlueprintFunctionLibrary
{
public:
	GENERATED_BODY()

	UFUNCTION(BlueprintCallable, Category="Crypto")
	FString GetMD5Sum(FString InputText);

	UFUNCTION(BlueprintCallable, Category = "Crypto")
		static FString GenerateToken();
	

	UFUNCTION(BlueprintCallable, Category = "Crypto")
		static FString Encrypt(FString InputText, FString Key);

	UFUNCTION(BlueprintCallable, Category = "Crypto")
		static FString Decrypt(FString InputText, FString Key);
};
