// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerStatRowWidget.generated.h"

class UImage;
class UTextBlock;
UCLASS()
class B1_API UPlayerStatRowWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void SetPlayerName(const FText& Text);
	void SetKills (const FText& Text);
	void SetDeaths (const FText& Text);
	void SetTeam (const FText& Text);
	void SetPlayerIndicatorVisibility (bool Visible);
	
protected:
	UPROPERTY(meta = (BindWidget))
	UTextBlock* PlayerNameTextBlock;

	UPROPERTY(meta = (BindWidget))
		UTextBlock* KillsTextBlock;

	UPROPERTY(meta = (BindWidget))
		UTextBlock* DeathsNameTextBlock;

	UPROPERTY(meta = (BindWidget))
		UTextBlock* TeamNameTextBlock;

	UPROPERTY(meta = (BindWidget))
		UImage* PlayerIndicatorImage;
};
