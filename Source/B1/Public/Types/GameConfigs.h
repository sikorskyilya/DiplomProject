// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "GameConfigs.generated.h"

USTRUCT(BlueprintType)
struct FGameConfig : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		int32 NumOfRounds;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		int32 RoundTime;
};