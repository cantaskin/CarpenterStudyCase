// Fill out your copyright notice in the Description page of Project Settings.


#include "CarpenterPlayerController.h"
#include "GameHud/CarpenterGameHUD.h"

void ACarpenterPlayerController::BeginPlay()
{
	Super::BeginPlay();
	GameHUD = Cast<ACarpenterGameHUD>(GetHUD());
}
