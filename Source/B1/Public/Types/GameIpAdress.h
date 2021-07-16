// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "GameIpAdress.generated.h"


USTRUCT(BlueprintType)
struct FGameIpAdrr : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		FString IpAdress;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		FString Type;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		int32 CountOfPlayers;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		int32 CurrentCountOfPlayers;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		int32 ServerStatus;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		int32 CurrentServerGameTime;
};