// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BasePickUp.generated.h"

class USphereComponent;

UCLASS()
class B1_API ABasePickUp : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABasePickUp();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UPROPERTY(VisibleAnywhere, Category="Pickup")
		USphereComponent* CollisionComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickup")
		float RespawnTime = 5.0f;

	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	bool CouldBeTaken() const;
private:
	virtual bool GivePickupTo(APawn* PlayerPawn);
	float RotationYaw = 0.0f;
	FTimerHandle RespawnTimerHandle;
	void GenerateRotationYaw();
	void PickupWasTaken();
	void Respawn();

};
