// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "AI/MyAIController.h"
#include "Types/B1CoreTypes.h"
#include "B1GameMode.generated.h"


class AMyAIController;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnFinishMatchStats, EMatchState, MatchState);

USTRUCT(BlueprintType)
struct FGameData
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Game", meta = (ClampMin = "1", ClampMax = "100"))
		int32 PlayerNum = 2;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Game", meta = (ClampMin = "1", ClampMax = "10"))
		int32 RoundsNum = 4;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Game", meta = (ClampMin = "3", ClampMax = "300"))
		int32 RoundTime = 15; // in sec

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		FLinearColor DefaultTeamColor = FLinearColor::Red;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		TArray<FLinearColor> TeamColors;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Game", meta = (ClampMin = "3", ClampMax = "20"))
		int32 RespawnTime = 15; // in sec
};

UCLASS(minimalapi)
class AB1GameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AB1GameMode();

	FOnMatchStateChangedSignature OnMatchStateChanged;

	UPROPERTY(BlueprintAssignable, Category = "Test")
		FOnFinishMatchStats OnTestDelegate;

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void Funqwe();

	virtual void StartPlay() override;

	virtual UClass* GetDefaultPawnClassForController_Implementation(AController* InController) override;

	void Killed(AController* KillerController, AController* VictimController);
	
	UFUNCTION(BlueprintCallable)
	FGameData GetGameData() const {return GameData;}

	UFUNCTION(BlueprintCallable)
	int32 GetCurrentRoundNum() const {return CurrentRound;}
	UFUNCTION(BlueprintCallable)
	int32  GetRoundSecondsRemaining() const {return RoundCountDown;}

	UPROPERTY(BlueprintReadOnly, Category = "Timer");
	FTimerHandle GameRoundTimerHandle;

	UFUNCTION(BlueprintCallable)
	void MatchCreation();

	void RespawnRequest(AController* Controller);

protected:
	UPROPERTY(EditDefaultsOnly, Category="Game")
		TSubclassOf<AMyAIController> AIControllerClass;

	UPROPERTY(EditDefaultsOnly, Category="Game")
		TSubclassOf<APawn> AIPawnClass;


	UPROPERTY(EditDefaultsOnly, Category="Game")
	FGameData GameData;

private:
	EMatchState MatchState = EMatchState::WaitingToStart;

	void SetMatchState(EMatchState State);

	void SpawnBots();
	void StartRound();
	void GameTimerUpdate();
	UFUNCTION(BlueprintCallable)
	void ResetPlayers();
	UFUNCTION(BlueprintCallable)
	void ResetOnePlayer(AController* Controller);

	void CreateTeamsInfo();
	FLinearColor DetermineColorByTeamID(int32 TeamID) const;
	void SetPlayerColor(AController* Controller);

	int32 CurrentRound = 1;
	int32 RoundCountDown = 0;
	
	void LogPlayerInfo();

	void StartRespawn(AController* Controller);
	void GameOver();
};



