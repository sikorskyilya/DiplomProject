// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Sound/SoundCue.h"
#include "Components/AudioComponent.h"
#include "PlayerBaseWeapon.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FOnClipEmptySignatyre, APlayerBaseWeapon*);

class USkeletalMeshComponent;
USTRUCT(BlueprintType)
struct FAmmoData
{
	GENERATED_USTRUCT_BODY()

		UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
		int32 Bullets;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon", meta = (EditCondition = "!Infinite"))
		int32 Clips; 

		UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
		bool Infinite;
};

USTRUCT(BlueprintType)
struct FWeaponUIData
{
	GENERATED_USTRUCT_BODY()

		UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
		UTexture2D* MainIcon;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
		UTexture2D* CrossHairIcon;
};


UCLASS()
class B1_API APlayerBaseWeapon : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	APlayerBaseWeapon();
	FOnClipEmptySignatyre  OnClipEmpty;

	UFUNCTION(BlueprintCallable, Category = "Weapon")
		virtual void StartFire();
	bool TryToAddAmmo(int32 ClipAmoun);
	virtual void StopFire();
	void ChangeClip();
	bool CanReload() const;
	FWeaponUIData GetUIData() const { return WeaponUI; }
	FAmmoData GetAmmoData() const { return CurrentAmmo; }
	bool IsAmmoEmpty() const;
	bool IsAmmoFull() const;
protected:
	// Called when the game starts or when spawned 
	virtual void BeginPlay() override;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
		FName MuzzleSocketName = "MazzleSocket";

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
		float TraceMaxDistance = 1500.0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
		FAmmoData DefaultAmmo{15, 10, false};
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Audio")
		USoundCue* propellerAudioCue;

	//UPROPERTY(BlueprintReadOnly, Category = "Audio")
	//	USoundCue* propellerStartupCue;

	UPROPERTY(BlueprintReadOnly, Category = "Audio")
		UAudioComponent* propellerAudioComponent;

	UPROPERTY(VisibleAnyWhere, BlueprintReadWrite, Category = "Components")
		USkeletalMeshComponent* WeaponMesh;

	virtual void MakeShot();
APlayerController* GetPlayerController() const;
	bool GetPlayerViewPoint(FVector& ViewLocation, FRotator& ViewRotation) const;
	FVector GetMuzzleWorldLocation() const; 
	virtual bool GetTraceData(FVector& TraceStart, FVector& TraceEnd) const;
	void MakeHit(FHitResult& HitResult, const FVector& TraceStart, const FVector& TraceEnd);
	void MakeDamage(const FHitResult& HitResult);
	
	UPROPERTY(VisibleAnyWhere, BlueprintReadWrite)
		float DamageAmount = 10.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
	FWeaponUIData WeaponUI;

	void DecreaseAmmo();
	
	bool IsClipEmpty() const;
	
	void LogAmmo();

private:
	FAmmoData CurrentAmmo;
	AController* GetController() const;
};
