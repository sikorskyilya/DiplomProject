// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTNeedAmmoDecorator.h"
#include "AIController.h"
#include "MyUtils.h"
#include "Weapon/WeaponActorComponent.h"


UBTNeedAmmoDecorator::UBTNeedAmmoDecorator()
{
	NodeName = "Need Ammo";
}

bool UBTNeedAmmoDecorator::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	const auto Controller = OwnerComp.GetAIOwner();
	if (!Controller) return false;

	const auto WeaponComponent = MyUtils::GetPlayerComponent<UWeaponActorComponent>(Controller->GetPawn());
	if (!WeaponComponent) return false;

	return WeaponComponent->NeedAmmo(WeaponType);

}