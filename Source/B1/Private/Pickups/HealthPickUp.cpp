// Fill out your copyright notice in the Description page of Project Settings.


#include "Pickups/HealthPickUp.h"
#include "Components/HealthComponent.h"
#include "MyUtils.h"


DEFINE_LOG_CATEGORY_STATIC(LogHeallthPickup, All, All);

AHealthPickUp::AHealthPickUp()
{
	//Effects = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Effect"));

}

bool AHealthPickUp::GivePickupTo(APawn* PlayerPawn)
{
	const auto HealthComponent = MyUtils::GetPlayerComponent<UHealthComponent>(PlayerPawn);
	if (!HealthComponent) return false;
	return HealthComponent->TryToAddHealth(HealthAmount);
}