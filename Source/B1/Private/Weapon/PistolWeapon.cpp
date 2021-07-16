// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/PistolWeapon.h"
#include "DrawDebugHelpers.h"
#include "Components/AudioComponent.h"
#include "Engine/World.h"

void APistolWeapon::StartFire()
{
	MakeShot();
}

void APistolWeapon::MakeShot()
{
	if (!GetWorld() || IsAmmoEmpty()) return;
	FVector TraceStart, TraceEnd;
	
	//USoundCue* propellerAudioCue;
	//UAudioComponent* audiocomp;
	propellerAudioComponent->Play(0.0f);
	//propellerAudioComponent->SetSound(propellerAudioCue);

	if (!GetTraceData(TraceStart, TraceEnd)) return;
	FHitResult HitResult;
	MakeHit(HitResult, TraceStart, TraceEnd);
	if (HitResult.bBlockingHit)
	{
		MakeDamage(HitResult);
		//DrawDebugLine(GetWorld(), GetMuzzleWorldLocation(), HitResult.ImpactPoint, FColor::Red, false, 3.0f, 0, 3.0f);

		DrawDebugSphere(GetWorld(), HitResult.ImpactPoint, 10.0f, 12, FColor::Red, false, 2.4f);
	}
	else
	{
		//DrawDebugLine(GetWorld(), GetMuzzleWorldLocation(), TraceEnd, FColor::Red, false, 3.0f, 0, 3.0f);
	}
	DecreaseAmmo();
}

bool APistolWeapon::GetTraceData(FVector& TraceStart, FVector& TraceEnd) const
{
	FVector ViewLocation;
	FRotator ViewRotation;
	if (!GetPlayerViewPoint(ViewLocation, ViewRotation)) return false;
	const auto HalfRad = FMath::DegreesToRadians(BulletSpread);
	TraceStart = ViewLocation;
	const FVector ShootDirection = FMath::VRandCone(ViewRotation.Vector(), HalfRad);
	TraceEnd = TraceStart + ShootDirection * TraceMaxDistance;
	return true;
}