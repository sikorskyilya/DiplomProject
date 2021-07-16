#include "HUD/GameOverWidget.h"
#include "../B1GameMode.h"
#include "../Player/MyPlayerState.h"
#include "HUD/PlayerStatRowWidget.h"
#include "Components/VerticalBox.h"
#include "MyUtils.h"

bool UGameOverWidget::Initialize()
{
	if (GetWorld())
	{
		const auto GameMode = Cast<AB1GameMode>(GetWorld()->GetAuthGameMode());
		if (GameMode)
		{
			GameMode->OnMatchStateChanged.AddUObject(this, &UGameOverWidget::OnMatchStateChanged);
		}
	}
	return Super::Initialize();
}

void UGameOverWidget::OnMatchStateChanged(EMatchState State)
{
	
	if (State == EMatchState::GameOver)
	{
		UpdatePlayersStat();
		UE_LOG(LogTemp, Warning, TEXT("Some warning message"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Fallllllll"));
	}
}

void UGameOverWidget::UpdatePlayersStat()
{
	/*if (!GetWorld() || !PlayerStatBox) return;

	PlayerStatBox->ClearChildren();

	for (auto It = GetWorld()->GetControllerIterator(); It; ++It)
	{
		const auto Controller = It->Get();
		if(!Controller) continue;

		const auto Playerstate = Cast<AMyPlayerState>(Controller->PlayerState);
		if(!Playerstate) continue;

		const auto PlayerStatRowWidget = CreateWidget<UPlayerStatRowWidget>(GetWorld(), PlayerStatRowWidgetClass);
		if(!PlayerStatRowWidget) continue;

		PlayerStatRowWidget->SetPlayerName(FText::FromString(Playerstate->GetPlayerName()));
		PlayerStatRowWidget->SetKills(MyUtils::TextFromInt(Playerstate->GetKillsNum()));
		PlayerStatRowWidget->SetDeaths(MyUtils::TextFromInt(Playerstate->GetDeathNum()));
		PlayerStatRowWidget->SetTeam(MyUtils::TextFromInt(Playerstate->GetTeamID()));
		PlayerStatRowWidget->SetPlayerIndicatorVisibility(Controller->IsPlayerController());

		PlayerStatBox->AddChild(PlayerStatRowWidget);

	}*/
}
