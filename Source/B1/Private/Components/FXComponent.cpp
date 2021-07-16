// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/FXComponent.h"
#include "NiagaraFunctionLibrary.h"




UFXComponent::UFXComponent()
{
	
	PrimaryComponentTick.bCanEverTick = false;

}

void UFXComponent::PlayImpcatFX(const FHitResult& HitResult)
{
	UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), Effect, HitResult.ImpactPoint, HitResult.ImpactPoint.Rotation());
}
