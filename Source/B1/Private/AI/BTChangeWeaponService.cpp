// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTChangeWeaponService.h"
#include "MyUtils.h"
#include "AIController.h"
#include "Weapon/WeaponActorComponent.h"

UBTChangeWeaponService::UBTChangeWeaponService()
{
	NodeName = "Change Weapon";
}


void UBTChangeWeaponService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	const auto Controller = OwnerComp.GetAIOwner();
	if (Controller)
	{
		const auto WeaponComponent = MyUtils::GetPlayerComponent<UWeaponActorComponent>(Controller->GetPawn());
		if (WeaponComponent && Probability > 0 && FMath::FRand() <= Probability)
		{
			WeaponComponent->NextWeapon();
		}
	}


	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
}