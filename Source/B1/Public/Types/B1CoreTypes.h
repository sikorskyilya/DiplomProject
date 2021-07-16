// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class EMatchState : uint8
{
	WaitingToStart = 0,
	InProgress,
	Pause,
	GameOver
};

DECLARE_MULTICAST_DELEGATE_OneParam(FOnMatchStateChangedSignature, EMatchState);

//DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnFinishMatchStats, EMatchState, MatchState);
//DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnFinishMatch, EMatchState, Finish);