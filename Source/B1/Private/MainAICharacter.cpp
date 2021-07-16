// Fill out your copyright notice in the Description page of Project Settings.


#include "MainAICharacter.h"
#include "AI/MyAIController.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Weapon/AIWeaponComponent.h"
#include "BrainComponent.h"

AMainAICharacter::AMainAICharacter(const FObjectInitializer& ObjInit) :
	Super(ObjInit.SetDefaultSubobjectClass<UAIWeaponComponent>("AIWeaponComponent"))
{
	
	AutoPossessAI = EAutoPossessAI::Disabled;
	AIControllerClass = AMyAIController::StaticClass();
	bUseControllerRotationYaw = false;
	if (GetCharacterMovement())
	{
		GetCharacterMovement()->bUseControllerDesiredRotation = true;
		GetCharacterMovement()->RotationRate = FRotator(0.0f, 200.0f, 0.0f);
	}
}

void AMainAICharacter::OnDeath()
{
	Super::OnDeath();

	const auto MController = Cast<AAIController>(Controller);
	if (MController && MController->BrainComponent)
	{
		MController->BrainComponent->Cleanup();
	}
}
