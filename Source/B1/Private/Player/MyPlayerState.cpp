// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/MyPlayerState.h"

DEFINE_LOG_CATEGORY_STATIC(LogPlayerState, All, All);

void AMyPlayerState::LogInfo()
{
	UE_LOG(LogPlayerState, Display, TEXT("TeamID: %i, Kills: %i, Deaths:%i"), TeamID, KillsNum, DeathNum);
}
