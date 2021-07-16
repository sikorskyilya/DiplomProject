// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/MainPlayerController.h"
#include "Components/RespawnComponent.h"


AMainPlayerController::AMainPlayerController()
{

	ARespawnComponent = CreateDefaultSubobject<URespawnComponent>("ARespawnComponent");

}