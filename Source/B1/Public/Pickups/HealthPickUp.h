// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Pickups/BasePickUp.h"
#include "HealthPickUp.generated.h"

/**
 * 
 */
UCLASS()
class B1_API AHealthPickUp : public ABasePickUp
{
	GENERATED_BODY()

public:
	AHealthPickUp();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickup", meta = (ClampMin = "1.0", ClampMax = "100.0"))
		float HealthAmount = 100.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickup")
		UParticleSystemComponent* Effects;

private:
	virtual bool GivePickupTo(APawn* PlayerPawn) override;
};
