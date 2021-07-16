// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "MyPlayerState.generated.h"

/**
 * 
 */
UCLASS()
class B1_API AMyPlayerState : public APlayerState
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = "PlayerInfo")
	void SetTeamID(int32 ID) { TeamID = ID; }
	UFUNCTION(BlueprintCallable, Category = "PlayerInfo")
	int32 GetTeamID() const { return TeamID; }

	void SetTeamColor(const FLinearColor& Color) { TeamColor = Color; }
	UFUNCTION(BlueprintCallable, Category = "PlayerInfo")
	FLinearColor GetTeamColor() const { return TeamColor; }

	void AddKill() { ++KillsNum; }
	UFUNCTION(BlueprintCallable, Category = "PlayerInfo")
	int32 GetKillsNum() const { return KillsNum; }

	void AddDeath() { ++DeathNum; }
	UFUNCTION(BlueprintCallable, Category = "PlayerInfo")
	int32 GetDeathNum() const { return DeathNum; }

	UFUNCTION(BlueprintCallable)
	void LogInfo();


private:
	int32 TeamID;
	FLinearColor TeamColor;

	int32 KillsNum = 0;
	int32 DeathNum = 0;


};
