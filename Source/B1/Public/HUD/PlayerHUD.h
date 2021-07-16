
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "PlayerHudWidget.h"
#include "Types/B1CoreTypes.h"
#include "PlayerHUD.generated.h"

/**
 * 
 */
UCLASS()
class B1_API APlayerHUD : public AHUD
{
	GENERATED_BODY()
	
public:
	virtual void DrawHUD() override;



protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
		TSubclassOf<UUserWidget> PlayerHUDWidgetClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
		TSubclassOf<UUserWidget> GameOverWidgetClass;

	virtual void BeginPlay() override;

private:

	UPROPERTY()
	TMap<EMatchState, UUserWidget*> GameWidgets;

	UPROPERTY()
		UUserWidget* CurrentWidget = nullptr;

	void DrawCrossHair();
	void OnMatchStateChanged(EMatchState State);
};
