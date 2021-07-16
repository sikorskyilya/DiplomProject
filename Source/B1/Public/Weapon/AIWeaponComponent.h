// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapon/WeaponActorComponent.h"
#include "AIWeaponComponent.generated.h"

/**
 * 
 */
UCLASS()
class B1_API UAIWeaponComponent : public UWeaponActorComponent
{
	GENERATED_BODY()
public:
		virtual void StartFire() override;
		virtual void NextWeapon() override;
};
