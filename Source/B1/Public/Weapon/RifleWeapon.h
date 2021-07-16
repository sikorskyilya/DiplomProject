// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapon/PlayerBaseWeapon.h"
#include "RifleWeapon.generated.h"

/**
 * 
 */
UCLASS()
class B1_API ARifleWeapon : public APlayerBaseWeapon
{
	GENERATED_BODY()
public:
	virtual void StartFire() override;
	virtual void StopFire() override;

protected:
	virtual void MakeShot() override;
	virtual bool GetTraceData(FVector& TraceStart, FVector& TraceEnd) const override;
	UPROPERTY(VisibleAnyWhere, BlueprintReadWrite)
		float TimeBetweenShot = 0.1f;
	UPROPERTY(VisibleAnyWhere, BlueprintReadWrite)
		float BulletSpread = 1.5f;
private:
	FTimerHandle ShotTimerHandle;
};
