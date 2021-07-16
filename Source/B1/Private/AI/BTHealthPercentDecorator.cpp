// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTHealthPercentDecorator.h"
#include "MyUtils.h"
#include "AIController.h"
#include "Components/HealthComponent.h"

UBTHealthPercentDecorator::UBTHealthPercentDecorator()
{
	NodeName = "HealthPercent";
}


bool UBTHealthPercentDecorator::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	const auto Controller = OwnerComp.GetAIOwner();
	if (!Controller) return false;

	const auto HealthComponent = MyUtils::GetPlayerComponent<UHealthComponent>(Controller->GetPawn());
	if (!HealthComponent || HealthComponent->IsDead()) return false;
	return HealthComponent->GetHealthPercent() <= HealthPercent;
}