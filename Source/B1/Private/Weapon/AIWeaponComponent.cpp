// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/AIWeaponComponent.h"
#include "Weapon/PlayerBaseWeapon.h"



void UAIWeaponComponent::StartFire()
{
	UE_LOG(LogTemp, Warning, TEXT("AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA"));
	if (!CanFire()) return;
	if (CurrentWeapon->IsAmmoEmpty())
	{
		
		NextWeapon();
	}
	else
	{
		CurrentWeapon->StartFire();
	}
}
void UAIWeaponComponent::NextWeapon()
{
	if (!CanEquip()) return;

	int32 NextIndex = (CurrentWeaponIndex + 1) % Weapons.Num();
	while (NextIndex != CurrentWeaponIndex)
	{
		if (!Weapons[NextIndex]->IsAmmoEmpty()) break;
		NextIndex = (NextIndex + 1) % Weapons.Num();
	}

	if (CurrentWeaponIndex != NextIndex)
	{
		CurrentWeaponIndex = NextIndex;
		EquipWeapon(CurrentWeaponIndex);
	}


}