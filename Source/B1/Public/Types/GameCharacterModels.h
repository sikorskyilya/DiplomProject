// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include <Runtime/UMG/Public/Components/Image.h>
#include "GameCharacterModels.generated.h"


USTRUCT(BlueprintType)
struct FGameCharacterModels : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

		UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
			int32 Index;

		UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
			FString ObjectName;

		UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
			USkeletalMesh* CharacterModel;

		UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
			UTexture* CharacterImage;

		UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
			float PriseInGold;

		UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
			float PriseInSilver;

		UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
			bool EnableToBuy;
};