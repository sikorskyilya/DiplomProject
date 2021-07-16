// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MainPlayerController.generated.h"

class URespawnComponent;


UCLASS()
class B1_API AMainPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AMainPlayerController();


protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	URespawnComponent* ARespawnComponent;
};
