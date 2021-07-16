// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PlayerBaseWeapon.h"
#include "WeaponActorComponent.generated.h"


class APlayerBaseWeapon;

USTRUCT(BlueprintType)
struct FWeaponData
{
	GENERATED_USTRUCT_BODY()

		UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
		TSubclassOf<APlayerBaseWeapon> WeaponClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
		UAnimMontage* ReloadAnimMontage;
};




UCLASS(Blueprintable, meta = (BlueprintSpawnableComponent))
class B1_API UWeaponActorComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UWeaponActorComponent();
	UFUNCTION(BlueprintCallable, Category = "Shooting")
	virtual void StartFire();
	UFUNCTION(BlueprintCallable, Category = "Shooting")
	virtual void NextWeapon();
	UFUNCTION(BlueprintCallable, Category = "Shooting")
	void StopFire();
	UFUNCTION(BlueprintCallable, Category = "Shooting")
	void Reload();
	UFUNCTION(BlueprintCallable, Category = "Shooting")
		void ChangeClip();

	bool GetWeaponUIData(FWeaponUIData& UIData) const;
	UFUNCTION(BlueprintCallable, Category = "Shooting")
	bool GetWeaponAmmoData(FAmmoData& AmmoData) const;
	bool TryToAddAmmo(TSubclassOf<APlayerBaseWeapon> WeaponType, int32 ClipAmount);
	bool NeedAmmo(TSubclassOf<APlayerBaseWeapon> WeaponType);
protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	FName WeaponAttachPointName = "WeaponSocket";

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
		FName WeaponArmorySocketName = "spine_01Socket";

	UPROPERTY(EditDefaultsOnly, Category = "Animation")
		UAnimMontage* EquiAnimMontage;
	UPROPERTY()
		APlayerBaseWeapon* CurrentWeapon = nullptr;
	UPROPERTY()
		TArray<APlayerBaseWeapon*> Weapons;
	int32 CurrentWeaponIndex = 0;
	bool CanFire() const;
	bool CanEquip() const;
	void EquipWeapon(int32 WeaponIndex);

public:	

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
		TArray<FWeaponData> WeaponData;
private:
	

	void AttachWeaponToSocket(APlayerBaseWeapon* Weapon, USceneComponent* SceneComponent, const FName& SocketName);
	UPROPERTY()
		UAnimMontage* CurrentReloadAnimMontage = nullptr;

	
	bool EquipAnimInProgress = false;
	bool ReloadAnimInProgress = false;

	bool CanReload() const;

	
	void SpawnWeapons();
	void OnEquipFinished(USkeletalMeshComponent* MeshComp);
	void OnReloadFinished(USkeletalMeshComponent* MeshComp);

	void InitAnimations();
	void PlayAnimMontage(UAnimMontage* Animation);

	void OnEmptyClip(APlayerBaseWeapon* AmmoEmptyWeapon);
	


	template<typename T>
	T* FindNotifyByClass(UAnimSequenceBase* Animation)
	{
		if (!Animation) return nullptr;
		const auto NotifyEvents = Animation->Notifies;
		for (auto NotifyEvent : NotifyEvents)
		{
			auto AnimNotify = Cast<T>(NotifyEvent.Notify);
			if (AnimNotify)
			{
				//UE_LOG(LogTemp, Warning, TEXT("Notif"));
				return AnimNotify;
			}
		}
		return nullptr;

	}
};
