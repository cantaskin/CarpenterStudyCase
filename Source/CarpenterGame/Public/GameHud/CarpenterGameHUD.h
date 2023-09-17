// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "CarpenterGameHUD.generated.h"

/**
 * 
 */
UCLASS()
class CARPENTERGAME_API ACarpenterGameHUD : public AHUD
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;
	void AddOrderWidget(int32 X);

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UMoneyWidget> MoneyWidget;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UOrderWidget> OrderWidget;

	UPROPERTY()
	UMoneyWidget *MoneyWidgetAccess;

	UPROPERTY()
	UOrderWidget* OrderWidgetAccess;

	void AddMoneyWidget();
};
