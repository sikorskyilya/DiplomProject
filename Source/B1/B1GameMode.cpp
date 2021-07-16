// Copyright Epic Games, Inc. All Rights Reserved.

#include "B1GameMode.h"
#include "B1Character.h"
#include "UObject/ConstructorHelpers.h"
#include "Player/MainPlayerCharacter.h"
#include "Player/MainPlayerController.h"
#include "MyAIController.h"
#include "HUD/PlayerHUD.h"
#include "Player/MyPlayerState.h"
#include "Components/RespawnComponent.h"
#include "MyUtils.h"
#include "EngineUtils.h"



AB1GameMode::AB1GameMode()
{
	DefaultPawnClass = AB1Character::StaticClass();
	PlayerControllerClass = AMainPlayerController::StaticClass();
	HUDClass = APlayerHUD::StaticClass();
	PlayerStateClass = AMyPlayerState::StaticClass();
}
void AB1GameMode::StartPlay()
{
	Super::StartPlay();
	Funqwe();
	
}

void AB1GameMode::StartRound()
{
	RoundCountDown = GameData.RoundTime;
	GetWorldTimerManager().SetTimer(GameRoundTimerHandle, this, &AB1GameMode::GameTimerUpdate, 1.0f, true);
}
void AB1GameMode::GameTimerUpdate()
{
	if (--RoundCountDown == 0)
	{
		GetWorldTimerManager().ClearTimer(GameRoundTimerHandle);

		if (CurrentRound + 1 <= GameData.RoundsNum)
		{
			++CurrentRound;
			ResetPlayers();
			StartRound();
		}
		else
		{
		GameOver();
			
		}
	}
}

void AB1GameMode::GameOver()
{
	LogPlayerInfo();

	for (auto Pawn : TActorRange<APawn>(GetWorld()))
	{
		if (Pawn)
		{
			Pawn->TurnOff();
			Pawn->DisableInput(nullptr);
		}
	}
	SetMatchState(EMatchState::GameOver);

}

UClass* AB1GameMode::GetDefaultPawnClassForController_Implementation(AController* InController)
{
	if (InController && InController->IsA<AAIController>())
	{
		return AIPawnClass;
	}
	return Super::GetDefaultPawnClassForController_Implementation(InController);
}

void AB1GameMode::Killed(AController* KillerController, AController* VictimController)
{
	const auto KillerPlayerState = KillerController ? Cast<AMyPlayerState>(KillerController->PlayerState) : nullptr;
	const auto VictimPlayerState = VictimController ? Cast<AMyPlayerState>(VictimController->PlayerState) : nullptr;
	if (KillerPlayerState)
	{
		KillerPlayerState->AddKill();
	}
	if (VictimPlayerState)
	{
		VictimPlayerState->AddDeath();
	}

	StartRespawn(VictimController);

}

void AB1GameMode::MatchCreation()
{
	SpawnBots();
	CreateTeamsInfo();
	CurrentRound = 1;
	StartRound();
	SetMatchState(EMatchState::InProgress);
}

void AB1GameMode::RespawnRequest(AController* Controller)
{
		ResetOnePlayer(Controller);
}

void AB1GameMode::SetMatchState(EMatchState State)
{
	if(MatchState == State) return;

	MatchState = State;
	OnMatchStateChanged.Broadcast(MatchState);
	OnTestDelegate.Broadcast(MatchState);
}

void AB1GameMode::SpawnBots()
{
	if (!GetWorld()) return;

	for (int32 i = 0; i < GameData.PlayerNum - 1; ++i)
	{
		FActorSpawnParameters SpawnInfo;
		SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		const auto AIController = GetWorld()->SpawnActor<AAIController>(AIControllerClass, SpawnInfo);
		RestartPlayer(AIController);
	}
}

void AB1GameMode::ResetPlayers()
{
	if (!GetWorld()) return;

	for (auto It = GetWorld()->GetControllerIterator(); It; ++It)
	{
		ResetOnePlayer(It->Get());
	}
}

void AB1GameMode::ResetOnePlayer(AController* Controller)
{
	if (Controller && Controller->GetPawn())
	{
		Controller->GetPawn()->Reset();
	}
	RestartPlayer(Controller);
	SetPlayerColor(Controller);
}

void AB1GameMode::CreateTeamsInfo()
{
	if (!GetWorld()) return;

	int32 TeamID = 1;
	for (auto It = GetWorld()->GetControllerIterator(); It; ++It)
	{
		const auto Controller = It->Get();
		if (!Controller) continue;

		const auto PlayerState = Cast<AMyPlayerState>(Controller->PlayerState);
		if(!PlayerState) continue;

		PlayerState->SetTeamID(TeamID);
		PlayerState->SetTeamColor(DetermineColorByTeamID(TeamID));
		//PlayerState->SetPlayerName(Controller->IsPlayerController() ? PlayerState->GetPlayerName() : "Bot");
		PlayerState->SetPlayerName(PlayerState->GetPlayerName());
		SetPlayerColor(Controller);
		TeamID = TeamID == 1 ? 2 : 1;
	}
}
FLinearColor AB1GameMode::DetermineColorByTeamID(int32 TeamID) const
{
	if (TeamID - 1 < GameData.TeamColors.Num())
	{
		return GameData.TeamColors[TeamID - 1];
	}
	return GameData.DefaultTeamColor;
}
void AB1GameMode::SetPlayerColor(AController* Controller)
{
	if (!Controller) return;

	const auto Character = Cast<AMainPlayerCharacter>(Controller->GetPawn());
	if (!Character) return;

	const auto PlayerState = Cast<AMyPlayerState>(Controller->PlayerState);
	if (!PlayerState) return;

	Character->SetPlayerColor(PlayerState->GetTeamColor());

}

void AB1GameMode::LogPlayerInfo()
{
	if (!GetWorld()) return;

	for (auto It = GetWorld()->GetControllerIterator(); It; ++It)
	{
		const auto Controller = It->Get();
		if (!Controller) continue;

		const auto PlayerState = Cast<AMyPlayerState>(Controller->PlayerState);
		if (!PlayerState) continue;

		PlayerState->LogInfo(); 
	}


}

void AB1GameMode::StartRespawn(AController* Controller)
{
	const auto RespawnComponent = MyUtils::GetPlayerComponent<URespawnComponent>(Controller);
	if(!RespawnComponent) return;

	RespawnComponent->Respawn(GameData.RespawnTime);

}