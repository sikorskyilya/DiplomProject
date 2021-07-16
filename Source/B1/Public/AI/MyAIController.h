// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "MyAIController.generated.h"

class UMainAIPerceptionComponent;
class URespawnComponent;


UCLASS()
class B1_API AMyAIController : public AAIController
{
	GENERATED_BODY()

public:
	AMyAIController();
	
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
		UMainAIPerceptionComponent* AiPerceptionComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
		URespawnComponent* ARespawnComponent;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
		FName FocusOnKeyName = "EnemyActor";


	virtual void  OnPossess(APawn* InPawn) override;
	virtual void  Tick(float DeltaTime) override;

private:
	AActor* GetFocusOnActor() const;



};
