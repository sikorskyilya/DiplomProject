// Fill out your copyright notice in the Description page of Project Settings.


#include "GameDataWidget.h"
#include "../B1GameMode.h"
#include "Player/MyPlayerState.h"
int32 UGameDataWidget::GetKillsNum() const
{
	const auto PlayerState = GetPlayerState();
	return PlayerState ? PlayerState->GetKillsNum() : 0;
}

int32 UGameDataWidget::GetCurrentRoundNum() const
{
	const auto GameMode = GetGameMode();
	return GameMode ? GameMode->GetCurrentRoundNum() : 0;
}

int32 UGameDataWidget::GetTotalRoundsNum() const
{
	const auto GameMode = GetGameMode();
	return GameMode ? GameMode->GetGameData().RoundsNum : 0;
}

int32 UGameDataWidget::GetRoundSecondsRemaining() const
{
	const auto GameMode = GetGameMode();
	return GameMode ? GameMode->GetRoundSecondsRemaining() : 0;
}

AB1GameMode* UGameDataWidget::GetGameMode() const
{
	return GetWorld() ? Cast<AB1GameMode>(GetWorld()->GetAuthGameMode()) :nullptr;
}

AMyPlayerState* UGameDataWidget::GetPlayerState() const
{
	return GetOwningPlayer() ? Cast< AMyPlayerState>(GetOwningPlayer()->PlayerState) : nullptr;
}