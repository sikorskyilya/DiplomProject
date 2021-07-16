// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Player/MainPlayerCharacter.h"
#include "MainAICharacter.generated.h"

class UBehaviorTree;


UCLASS()
class B1_API AMainAICharacter : public AMainPlayerCharacter
{
	GENERATED_BODY()

public:
	AMainAICharacter(const FObjectInitializer& ObjInit);
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AI")
		UBehaviorTree* UBehaviorTreeAsset;
protected:
	virtual void OnDeath();
};
