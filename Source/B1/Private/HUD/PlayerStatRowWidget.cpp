// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/PlayerStatRowWidget.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"

void UPlayerStatRowWidget::SetDeaths(const FText& Text)
{
	if(!DeathsNameTextBlock) return;
	DeathsNameTextBlock->SetText(Text);
}

void UPlayerStatRowWidget::SetPlayerName(const FText& Text)
{
	if(!PlayerNameTextBlock) return;
	PlayerNameTextBlock->SetText(Text);
}

void UPlayerStatRowWidget::SetKills(const FText& Text)
{
	if(!KillsTextBlock) return;
	KillsTextBlock->SetText(Text);
}

void UPlayerStatRowWidget::SetTeam(const FText& Text)
{
	if(!TeamNameTextBlock) return;
	TeamNameTextBlock->SetText(Text);
}

void UPlayerStatRowWidget::SetPlayerIndicatorVisibility(bool Visible)
{
	if(!PlayerIndicatorImage) return;
	PlayerIndicatorImage->SetVisibility(Visible ? ESlateVisibility::Visible : ESlateVisibility::Hidden);
}