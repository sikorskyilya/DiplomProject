// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BT_FireService.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "MyUtils.h"
#include "Weapon/WeaponActorComponent.h"



UBT_FireService::UBT_FireService()
{
	NodeName = "Fire";
}


void UBT_FireService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	const auto Controller = OwnerComp.GetAIOwner();
	const auto Blackboard = OwnerComp.GetBlackboardComponent();

	const auto HasAim = Blackboard && Blackboard->GetValueAsObject(EnemyActorKey.SelectedKeyName);

	if (Controller)
	{
		const auto WeaponComponent = MyUtils::GetPlayerComponent<UWeaponActorComponent>(Controller->GetPawn());
		if (WeaponComponent)
		{
			HasAim ? WeaponComponent->StartFire() : WeaponComponent->StopFire();
		}
	}


	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
}