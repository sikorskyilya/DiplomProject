// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/PlayerHUD.h"
#include "PlayerHudWidget.h"
#include "Engine/Canvas.h"
#include "Blueprint/UserWidget.h"
#include "../B1GameMode.h"

void APlayerHUD::DrawHUD()
{
	Super::DrawHUD();


	//DrawCrossHair();
}

void APlayerHUD::BeginPlay()
{
	Super::BeginPlay();
	//auto PlayerHUDWidget = CreateWidget<UPlayerHudWidget>(GetWorld(), PlayerHUDWidgetClass);
	/*GameWidgets.Add(EMatchState::InProgress, CreateWidget<UUserWidget>(GetWorld(), PlayerHUDWidgetClass));
	GameWidgets.Add(EMatchState::GameOver, CreateWidget<UUserWidget>(GetWorld(), GameOverWidgetClass));

	for(auto GameWidgetPair : GameWidgets)
	{
		const auto GameWidget = GameWidgetPair.Value;
		if (!GameWidget) continue;

		GameWidget->AddToViewport();
		GameWidget->SetVisibility(ESlateVisibility::Collapsed);
	}*/
	if (GetWorld())
	{
		const auto GameMode = Cast<AB1GameMode>(GetWorld()->GetAuthGameMode());
		if (GameMode)
		{
			GameMode->OnMatchStateChanged.AddUObject(this, &APlayerHUD::OnMatchStateChanged);
		}
	}
}

void APlayerHUD::DrawCrossHair()
{
	int32 SizeX = Canvas->SizeX;
	int32 SizeY = Canvas->SizeY;
	const TInterval<float> Center(SizeX * 0.5f, SizeY * 0.5f);

	const float HalfLineSize = 10.0f;
	const float LineThickness = 2.0f;
	const FLinearColor LineColor = FLinearColor::Green;

	DrawLine(Center.Min - HalfLineSize, Center.Max, Center.Min + HalfLineSize, Center.Max, LineColor, LineThickness);
	DrawLine(Center.Min, Center.Max - HalfLineSize, Center.Min, Center.Max + HalfLineSize, LineColor, LineThickness);
}

void APlayerHUD::OnMatchStateChanged(EMatchState State)
{
	UE_LOG(LogTemp, Warning, TEXT("Some warning message %s"), *UEnum::GetValueAsString(State));
	/*if (CurrentWidget)
	{
		CurrentWidget->SetVisibility(ESlateVisibility::Collapsed);
	}
	if (GameWidgets.Contains(State))
	{
		CurrentWidget = GameWidgets[State];
	}

	if (CurrentWidget)
	{
		CurrentWidget->SetVisibility(ESlateVisibility::Visible);
	}*/



	/*if (State == EMatchState::InProgress)
	{
		for (auto GameWidgetPair : GameWidgets)
		{
			GameWidgets.Remove(GameWidgetPair.Key);
		}
		GameWidgets.Add(EMatchState::InProgress, CreateWidget<UUserWidget>(GetWorld(), PlayerHUDWidgetClass));
		CurrentWidget = GameWidgets[State];
		CurrentWidget->AddToViewport();
		CurrentWidget->SetVisibility(ESlateVisibility::Visible);
	}
	else {
		for (auto GameWidgetPair : GameWidgets)
		{
			GameWidgets.Remove(GameWidgetPair.Key);
		}
		GameWidgets.Add(EMatchState::GameOver, CreateWidget<UUserWidget>(GetWorld(), GameOverWidgetClass));
		CurrentWidget = GameWidgets[State];
		CurrentWidget->AddToViewport();
		CurrentWidget->SetVisibility(ESlateVisibility::Visible);
	}*/
}

