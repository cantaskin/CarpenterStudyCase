// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "CarpenterPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class CARPENTERGAME_API ACarpenterPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;
	
	UPROPERTY(EditAnywhere)
	class ACarpenterGameHUD *GameHUD;


	
};
