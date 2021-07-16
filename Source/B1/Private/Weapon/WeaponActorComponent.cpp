// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/WeaponActorComponent.h"
#include "GameFramework/Character.h"
#include "Weapon/PlayerBaseWeapon.h"
#include "Animations/MyAnimNotify.h"
#include "Animations/MyReloadAnimNotify.h"

UWeaponActorComponent::UWeaponActorComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

}

void UWeaponActorComponent::BeginPlay()
{
	Super::BeginPlay();
	CurrentWeaponIndex = 0;
	SpawnWeapons();
	EquipWeapon(CurrentWeaponIndex);
	InitAnimations();
}


void UWeaponActorComponent::SpawnWeapons()
{
	ACharacter* character = Cast<ACharacter>(GetOwner());
	if (!character || !GetWorld())
	{
		return;
	}
	
	for (auto OneWeaponData : WeaponData)
	{
		auto Weapon = GetWorld()->SpawnActor<APlayerBaseWeapon>(OneWeaponData.WeaponClass);
		if (Weapon)
		{
			Weapon->OnClipEmpty.AddUObject(this, &UWeaponActorComponent::OnEmptyClip);
			Weapon->SetOwner(character);
			Weapons.Add(Weapon);
			
			AttachWeaponToSocket(Weapon, character->GetMesh(), WeaponArmorySocketName);
		}
	}
	
}

void UWeaponActorComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	CurrentWeapon = nullptr;
	for (auto Weapon : Weapons)
	{
		Weapon->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
		Weapon->Destroy();
	}
	Weapons.Empty();

	Super::EndPlay(EndPlayReason);
}

void UWeaponActorComponent::AttachWeaponToSocket(APlayerBaseWeapon* Weapon, USceneComponent* SceneComponent, const FName& SocketName)
{
	if (!Weapon || !SceneComponent) return;
	FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, false);
	Weapon->AttachToComponent(SceneComponent, AttachmentRules, SocketName);
}

void UWeaponActorComponent::EquipWeapon(int32 WeaponIndex)
{
	if (WeaponIndex < 0 || WeaponIndex >= Weapons.Num())
	{
		UE_LOG(LogTemp, Warning, TEXT("Invalid weapon index"));
		return;
	}
	ACharacter* character = Cast<ACharacter>(GetOwner());
	if (!character) return;
	
	if (CurrentWeapon)
	{
		CurrentWeapon->StopFire();
		AttachWeaponToSocket(CurrentWeapon, character->GetMesh(), WeaponArmorySocketName);
	}

	CurrentWeapon = Weapons[WeaponIndex];
	CurrentReloadAnimMontage = WeaponData[WeaponIndex].ReloadAnimMontage;
	const auto CurrentWeaponData = WeaponData.FindByPredicate([&](const FWeaponData& Data) {return Data.WeaponClass == CurrentWeapon->GetClass(); });//5-21
	CurrentReloadAnimMontage = CurrentWeaponData ? CurrentWeaponData->ReloadAnimMontage : nullptr;
	AttachWeaponToSocket(CurrentWeapon, character->GetMesh(), WeaponAttachPointName);
	EquipAnimInProgress = true;
	PlayAnimMontage(EquiAnimMontage);
}

bool UWeaponActorComponent::CanFire() const
{
	//UE_LOG(LogTemp, Warning, TEXT("Weapon is not working"));
	return CurrentWeapon && !EquipAnimInProgress && !ReloadAnimInProgress;
}

bool UWeaponActorComponent::CanReload() const
{
	return CurrentWeapon && !EquipAnimInProgress && !ReloadAnimInProgress && CurrentWeapon->CanReload();
}

bool UWeaponActorComponent::CanEquip() const
{
	return !EquipAnimInProgress && !ReloadAnimInProgress;
}

void UWeaponActorComponent::OnEquipFinished(USkeletalMeshComponent* MeshComp)
{
	ACharacter* Character = Cast<ACharacter>(GetOwner());
	if (!Character || MeshComp != Character->GetMesh()) return;
	//UE_LOG(LogTemp, Warning, TEXT("False"));
	EquipAnimInProgress = false;
}

void UWeaponActorComponent::OnReloadFinished(USkeletalMeshComponent* MeshComp)
{
	ACharacter* Character = Cast<ACharacter>(GetOwner());
	if (!Character || MeshComp != Character->GetMesh()) return;
	//UE_LOG(LogTemp, Warning, TEXT("False")); 
	ReloadAnimInProgress = false;
}


void UWeaponActorComponent::StartFire()
{
	if (!CanFire())return;
	CurrentWeapon->StartFire();
}
void UWeaponActorComponent::NextWeapon()
{
	if (!CanEquip()) return;
	CurrentWeaponIndex = (CurrentWeaponIndex + 1) % Weapons.Num();
	EquipWeapon(CurrentWeaponIndex);
}
void UWeaponActorComponent::StopFire()
{
	if (!CurrentWeapon)return;
	CurrentWeapon->StopFire();
}

void UWeaponActorComponent::Reload()
{
	ChangeClip();
}

void UWeaponActorComponent::PlayAnimMontage(UAnimMontage* Animation)
{
	ACharacter* character = Cast<ACharacter>(GetOwner());
	if (!character) return;

	character->PlayAnimMontage(Animation);
}

void UWeaponActorComponent::InitAnimations()
{
	
	auto EquipFinishedNotify = FindNotifyByClass<UMyAnimNotify>(EquiAnimMontage);
	if (EquipFinishedNotify)
	{
		//UE_LOG(LogTemp, Warning, TEXT("Notif"));
		EquipFinishedNotify->OnNotified.AddUObject(this, &UWeaponActorComponent::OnEquipFinished);
	}

	for (auto OneWeaponData : WeaponData)
	{
		auto ReloadFinishedNotify = FindNotifyByClass<UMyReloadAnimNotify>(OneWeaponData.ReloadAnimMontage);
		if (!ReloadFinishedNotify) continue;
		ReloadFinishedNotify->OnNotified.AddUObject(this, &UWeaponActorComponent::OnReloadFinished);
	}
}


void UWeaponActorComponent::OnEmptyClip(APlayerBaseWeapon* AmmoEmptyWeapon)
{
	if (!AmmoEmptyWeapon) return;
	if (CurrentWeapon == AmmoEmptyWeapon)
	{
		ChangeClip();
	}
	else
	{
		for (const auto Weapon : Weapons)
		{
			if (Weapon == AmmoEmptyWeapon)
			{
				Weapon->ChangeClip();
			}
		}
	}
}
void UWeaponActorComponent::ChangeClip()
{
	if (!CanReload()) return;
	CurrentWeapon->StopFire();
	CurrentWeapon->ChangeClip();
	ReloadAnimInProgress = true;
	PlayAnimMontage(CurrentReloadAnimMontage);
}

bool UWeaponActorComponent::GetWeaponUIData(FWeaponUIData& UIData) const
{
	if (CurrentWeapon)
	{
		UIData = CurrentWeapon->GetUIData();
		return true;
	}
	return false;
}
bool UWeaponActorComponent::GetWeaponAmmoData(FAmmoData& AmmoData) const
{
	if (CurrentWeapon)
	{
		AmmoData = CurrentWeapon->GetAmmoData();
	}
	return false;
}

bool UWeaponActorComponent::TryToAddAmmo(TSubclassOf<APlayerBaseWeapon> WeaponType, int32 ClipAmount)
{
	for (const auto Weapon : Weapons)
	{
		UE_LOG(LogTemp, Warning, TEXT("TryAdd for"));
		if (Weapon && Weapon->IsA(WeaponType))
		{
			UE_LOG(LogTemp, Warning, TEXT("TryAdd for if"));
			return Weapon->TryToAddAmmo(ClipAmount);
		}
	}
	UE_LOG(LogTemp, Warning, TEXT("TryAdd false"));
	return false;
}
bool UWeaponActorComponent::NeedAmmo(TSubclassOf<APlayerBaseWeapon> WeaponType)
{
	for (const auto Weapon : Weapons)
	{
		if (Weapon && Weapon->IsA(WeaponType))
		{
			return !Weapon->IsAmmoFull();
		}
	}
	return false;
}

