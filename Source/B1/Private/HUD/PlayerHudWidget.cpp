// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/PlayerHudWidget.h"
#include "Components/HealthComponent.h"
#include "Weapon/WeaponActorComponent.h"
#include "MyUtils.h"

float UPlayerHudWidget::GetPlayerHealthPercent() const
{
	const auto HealthComponent = MyUtils::GetPlayerComponent<UHealthComponent>(GetOwningPlayerPawn());
	if(!HealthComponent) return 0.0f;
	return HealthComponent->GetHealthPercent();
	//return 0.0f;
}


//float UPlayerHudWidget::GetHealthPercent() const
//{
//	/*const auto Player = GetOwningPlayerPawn();
//	if (!Player) return 0.0f;
//	const auto Component = Player->GetComponentByClass(UHealthComponent::StaticClass());
//	const auto HealthComponent = Cast<UHealthComponent>(Component);
//	if(!HealthComponent) return 0.0f;
//	return HealthComponent->GetHealthPercent();*/
//	return 0.0f;
//}

bool UPlayerHudWidget::GetWeaponUIData(FWeaponUIData& UIData) const
{
	const auto WeaponComponent = MyUtils::GetPlayerComponent<UWeaponActorComponent>(GetOwningPlayerPawn());
	if (!WeaponComponent) return false;

	return WeaponComponent->GetWeaponUIData(UIData);
}

bool UPlayerHudWidget::GetWeaponAmmoData(FAmmoData& AmmoData) const
{

	const auto WeaponComponent = MyUtils::GetPlayerComponent<UWeaponActorComponent>(GetOwningPlayerPawn());
	if (!WeaponComponent) return false;
	return WeaponComponent->GetWeaponAmmoData(AmmoData);
}
bool UPlayerHudWidget::IsPlayerAlive() const
{
	const auto HealthComponent = MyUtils::GetPlayerComponent<UHealthComponent>(GetOwningPlayerPawn());
	return HealthComponent && !HealthComponent->IsDead();
}
bool UPlayerHudWidget::IsPlayerSpectating() const
{
	const auto Controller = GetOwningPlayer();
	return Controller && Controller->GetStateName() == NAME_Spectating;
}