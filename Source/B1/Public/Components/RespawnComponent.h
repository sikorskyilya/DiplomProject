#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "RespawnComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class B1_API URespawnComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	URespawnComponent();

	void Respawn(int32 RespawnTime);

	UPROPERTY(BlueprintReadWrite, Category = "Time")
	int32 RespawnCountDown = 4;


private:
	FTimerHandle RespawnTimeHandle;
	

	void RespawnTimerUpdate();
};
