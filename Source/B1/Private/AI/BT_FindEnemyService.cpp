// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BT_FindEnemyService.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "MyUtils.h"
#include "AI/MainAIPerceptionComponent.h"


UBT_FindEnemyService::UBT_FindEnemyService()
{
	NodeName = "Find Enemy";
}


void UBT_FindEnemyService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	const auto Blackboard = OwnerComp.GetBlackboardComponent();
	if (Blackboard)
	{
		const auto Controller = OwnerComp.GetAIOwner();
		const auto PerceptionComponent = MyUtils::GetPlayerComponent<UMainAIPerceptionComponent>(Controller);
		if (PerceptionComponent)
		{
			Blackboard->SetValueAsObject(EnemyActorKey.SelectedKeyName, PerceptionComponent->GetClosestEnemy());
		}
	}
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
}

