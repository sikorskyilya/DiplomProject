// Fill out your copyright notice in the Description page of Project Settings.


#include "Pickups/MyAmmoPickUp.h"
#include "Components/HealthComponent.h"
#include "Weapon/WeaponActorComponent.h"
#include "MyUtils.h"

DEFINE_LOG_CATEGORY_STATIC(LogAmmoPickup, All, All);

bool AMyAmmoPickUp::GivePickupTo(APawn* PlayerPawn)
{
	const auto HealthComponent = MyUtils::GetPlayerComponent<UHealthComponent>(PlayerPawn);
	if (!HealthComponent || HealthComponent->IsDead()) return false;
	const auto WeaponComponent = MyUtils::GetPlayerComponent<UWeaponActorComponent>(PlayerPawn);
	if (!WeaponComponent)
	{
		UE_LOG(LogTemp, Warning, TEXT("Invalid Component"));
		return false;
	}
	return WeaponComponent->TryToAddAmmo(WeaponType, ClipsAmount);
}