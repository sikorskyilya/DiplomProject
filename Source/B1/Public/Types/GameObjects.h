// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "GameObjects.generated.h"

USTRUCT(BlueprintType)
struct FGameObject : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		int32 Index;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		USkeletalMesh* CharacterModel;

};