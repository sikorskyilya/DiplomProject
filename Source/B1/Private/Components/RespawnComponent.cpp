
#include "Components/RespawnComponent.h"
#include "../B1GameMode.h"

URespawnComponent::URespawnComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void URespawnComponent::Respawn(int32 RespawnTime)
{
	if(!GetWorld()) return;
	
	RespawnCountDown = RespawnTime;
	GetWorld()->GetTimerManager().SetTimer(RespawnTimeHandle, this, &URespawnComponent::RespawnTimerUpdate, 1.0f, true);

}

void URespawnComponent::RespawnTimerUpdate()
{
	if (--RespawnCountDown == 0)
	{
		if(!GetWorld()) return;
		GetWorld()->GetTimerManager().ClearTimer(RespawnTimeHandle);

		const auto GameMode = Cast<AB1GameMode>(GetWorld()->GetAuthGameMode());
		if(!GameMode) return;

		GameMode->RespawnRequest(Cast<AController>(GetOwner()));
	}
}
