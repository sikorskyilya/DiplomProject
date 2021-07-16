// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "BTNeedAmmoDecorator.generated.h"

class APlayerBaseWeapon;

UCLASS()
class B1_API UBTNeedAmmoDecorator : public UBTDecorator
{
	GENERATED_BODY()
	
public:
	UBTNeedAmmoDecorator();


protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
		TSubclassOf<APlayerBaseWeapon> WeaponType;


	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;


};
