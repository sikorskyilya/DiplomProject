
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MainPlayerCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;
class UWeaponActorComponent;
class UHealthComponent;
class UTextRenderComponent;
class USphereComponent;

UCLASS()
class B1_API AMainPlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMainPlayerCharacter(const FObjectInitializer& ObjInit);

protected:
	// Called when the game starts or when spawned
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
		UCameraComponent* CameraComponent;
	 
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
		USpringArmComponent* SpringArm;

	UFUNCTION(BlueprintCallable, Category = "Movement")
		float GetMovementDirection() const;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
		UHealthComponent* HealthComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
		UWeaponActorComponent* WeaponComponent = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Animation")
		UAnimMontage* DeathAnimMontage;

	UPROPERTY(EditDefaultsOnly, Category = "Movement")
		FVector2D LandedVelocity = FVector2D(500.0f, 1200.0f);

	UPROPERTY(EditDefaultsOnly, Category = "Movement")
		FVector2D LandedDamage = FVector2D(10.0f, 100.0f);

	UPROPERTY(EditDefaultsOnly, Category="Material")
		FName MaterialColorName = "Paint Color";

	virtual void OnDeath();

	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	void SetPlayerColor(const FLinearColor& Color);
private:
	void MoveForward(float Amount);
	void MoveRight(float Amount);
	
	void Turn(float Amount);
	void LookUp(float Amount);
	
	UFUNCTION()
		void OnGroundLanded(const FHitResult& Hit);

};
