 // Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/PlayerBaseWeapon.h"
#include "Components/SkeletalMeshComponent.h"
#include "DrawDebugHelpers.h"
#include "Engine/World.h"
#include "GameFramework/Character.h"
#include "GameFramework/Controller.h"


DEFINE_LOG_CATEGORY_STATIC(LogBaseWeapon, All, All);

APlayerBaseWeapon::APlayerBaseWeapon()
{
 	PrimaryActorTick.bCanEverTick = false;
	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>("WeaponMesh");
	SetRootComponent(WeaponMesh);

	static ConstructorHelpers::FObjectFinder<USoundCue> PunchSoundCueObject(TEXT("SoundCue'/Game/Audio/NewSoundCue.NewSoundCue'"));
	if (PunchSoundCueObject.Succeeded())
	{
		propellerAudioCue = PunchSoundCueObject.Object;

		propellerAudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("PunchAudioComponent"));
		propellerAudioComponent->SetupAttachment(RootComponent);
		//propellerAudioComponent->SetSound(propellerAudioCue);
	}
}

void APlayerBaseWeapon::BeginPlay()
{
	Super::BeginPlay();
	CurrentAmmo = DefaultAmmo;
	
}
void APlayerBaseWeapon::DecreaseAmmo()
{
	if (CurrentAmmo.Bullets == 0)
	{
		UE_LOG(LogBaseWeapon, Display, TEXT("Clip is empty"));
		return;
	}
	CurrentAmmo.Bullets--;
	if (IsClipEmpty() && !IsAmmoEmpty())
	{
		StopFire();
		OnClipEmpty.Broadcast(this);
	}
}
bool APlayerBaseWeapon::IsAmmoEmpty() const
{
	return !CurrentAmmo.Infinite && CurrentAmmo.Clips == 0 && IsClipEmpty();
}
bool APlayerBaseWeapon::IsClipEmpty() const
{
	return CurrentAmmo.Bullets == 0;
}
bool APlayerBaseWeapon::IsAmmoFull() const
{
	return CurrentAmmo.Clips == DefaultAmmo.Clips && CurrentAmmo.Bullets == DefaultAmmo.Bullets;
}
void APlayerBaseWeapon::ChangeClip()
{
	CurrentAmmo.Bullets = DefaultAmmo.Bullets;
	if (!CurrentAmmo.Infinite)
	{
		if (CurrentAmmo.Clips == 0)
		{
			UE_LOG(LogBaseWeapon, Display, TEXT("No more clips"));
			return;
		}
		CurrentAmmo.Clips--;
	}
	//UE_LOG(LogBaseWeapon, Display, TEXT("-----------Change clip------------"));
}
bool APlayerBaseWeapon::CanReload() const
{
	return CurrentAmmo.Bullets < DefaultAmmo.Bullets && CurrentAmmo.Clips>0;
}
void APlayerBaseWeapon::LogAmmo()
{
	FString AmmoInfo = "Ammo: " + FString::FromInt(CurrentAmmo.Bullets) + " / ";
	AmmoInfo += CurrentAmmo.Infinite ? "Infinite" : FString::FromInt(CurrentAmmo.Clips);
	UE_LOG(LogBaseWeapon, Display, TEXT("%s"), *AmmoInfo);
}
void APlayerBaseWeapon::StartFire()
{
	//MakeShot();
	//GetWorldTimerManager().SetTimer(ShotTimerHandle, this, &APlayerBaseWeapon::MakeShot, TimeBetweenShot, true);
}
bool APlayerBaseWeapon::TryToAddAmmo(int32 ClipAmoun)
{
	if (CurrentAmmo.Infinite || IsAmmoFull() || ClipAmoun <= 0) return false;
	if (IsAmmoEmpty())
	{
		CurrentAmmo.Clips = FMath::Clamp(ClipAmoun, 0, DefaultAmmo.Clips + 1);
		OnClipEmpty.Broadcast(this);
	}
	else if (CurrentAmmo.Clips < DefaultAmmo.Clips)
	{
		const auto NextClipsAmount = CurrentAmmo.Clips + ClipAmoun;
		if (DefaultAmmo.Clips - NextClipsAmount >= 0)
		{
			CurrentAmmo.Clips = NextClipsAmount;
		}
		else
		{
			CurrentAmmo.Clips = DefaultAmmo.Clips;
			CurrentAmmo.Bullets = DefaultAmmo.Bullets;
		}
	}
	return true;
}
void APlayerBaseWeapon::StopFire()
{
	//GetWorldTimerManager().ClearTimer(ShotTimerHandle);
}

void APlayerBaseWeapon::MakeShot()
{
	/*if (!GetWorld()) return;
	FVector TraceStart, TraceEnd;
	if (!GetTraceData(TraceStart, TraceEnd)) return;
	FHitResult HitResult;
	MakeHit(HitResult, TraceStart, TraceEnd);
	if (HitResult.bBlockingHit)
	{
		MakeDamage(HitResult);
		DrawDebugLine(GetWorld(), GetMuzzleWorldLocation(), HitResult.ImpactPoint, FColor::Red, false, 3.0f, 0, 3.0f);

		DrawDebugSphere(GetWorld(), HitResult.ImpactPoint, 10.0f, 24, FColor::Red, false, 5.0f);
	}
	else
	{
		DrawDebugLine(GetWorld(), GetMuzzleWorldLocation(), TraceEnd, FColor::Red, false, 3.0f, 0, 3.0f);
	}*/

}
APlayerController* APlayerBaseWeapon::GetPlayerController() const
{
	const auto Player = Cast<ACharacter>(GetOwner());
	if (!Player) return nullptr;

	return Player->GetController<APlayerController>();
}

bool APlayerBaseWeapon::GetPlayerViewPoint(FVector& ViewLocation, FRotator& ViewRotation) const
{
	const auto MCharacter = Cast<ACharacter>(GetOwner());
	if (!MCharacter) return false;

	if (MCharacter->IsPlayerControlled())
	{
		const auto Controller = GetPlayerController();
		if (!Controller) return false;
		Controller->GetPlayerViewPoint(ViewLocation, ViewRotation);
	}
	else
	{
		ViewLocation = GetMuzzleWorldLocation();
		ViewRotation = WeaponMesh->GetSocketRotation(MuzzleSocketName);
	}
	return true;
}
FVector APlayerBaseWeapon::GetMuzzleWorldLocation() const
{
	return WeaponMesh->GetSocketLocation(MuzzleSocketName);
}

bool APlayerBaseWeapon::GetTraceData(FVector& TraceStart, FVector& TraceEnd) const
{
	FVector ViewLocation;
	FRotator ViewRotation;
	if (!GetPlayerViewPoint(ViewLocation, ViewRotation)) return false;

	TraceStart = ViewLocation;
	const FVector ShootDirection = ViewRotation.Vector();
	TraceEnd = TraceStart + ShootDirection * TraceMaxDistance;
	return true;
}

void APlayerBaseWeapon::MakeHit(FHitResult& HitResult, const FVector& TraceStart, const FVector& TraceEnd)
{
	if (!GetWorld()) return;
	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActor(GetOwner());
	GetWorld()->LineTraceSingleByChannel(HitResult, TraceStart, TraceEnd, ECollisionChannel::ECC_Visibility, CollisionParams);

}

void APlayerBaseWeapon::MakeDamage(const FHitResult& HitResult) //возможно тут вылет
{
	const auto DamagedActor = HitResult.GetActor();
	if (!DamagedActor) return;
	DamagedActor->TakeDamage(DamageAmount, FDamageEvent(), GetController(), this);

}

AController* APlayerBaseWeapon::GetController() const
{
	const auto Pawn = Cast<APawn>(GetOwner());
	return Pawn ? Pawn->GetController() : nullptr;
}