// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Perception/AIPerceptionComponent.h"
#include "MainAIPerceptionComponent.generated.h"

/**
 * 
 */
UCLASS()
class B1_API UMainAIPerceptionComponent : public UAIPerceptionComponent
{
	GENERATED_BODY()
	
public:
	AActor* GetClosestEnemy() const;
};
