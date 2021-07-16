// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/MyAIController.h"
#include "MainAICharacter.h"
#include "AI/MainAIPerceptionComponent.h"
#include "Components/RespawnComponent.h"
#include "BehaviorTree/BlackboardComponent.h"

AMyAIController::AMyAIController()
{
	AiPerceptionComponent = CreateDefaultSubobject<UMainAIPerceptionComponent>("AiPerceptionComponent");
	SetPerceptionComponent(*AiPerceptionComponent);

	ARespawnComponent = CreateDefaultSubobject<URespawnComponent>("ARespawnComponent");

	bWantsPlayerState = true;
}



void AMyAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	
	const auto AICharacter = Cast<AMainAICharacter>(InPawn);
	if (!AICharacter) return;
	RunBehaviorTree(AICharacter->UBehaviorTreeAsset);


}



void AMyAIController::Tick(float DeltaTime)
{ 
	Super::Tick(DeltaTime);
	const auto AimActor = GetFocusOnActor();
	SetFocus(AimActor);

}


AActor* AMyAIController::GetFocusOnActor() const
{
	if (!GetBlackboardComponent()) return nullptr;
	return Cast<AActor>(GetBlackboardComponent()->GetValueAsObject(FocusOnKeyName));
}