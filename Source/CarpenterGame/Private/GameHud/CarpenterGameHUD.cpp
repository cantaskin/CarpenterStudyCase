// Fill out your copyright notice in the Description page of Project Settings.


#include "GameHud/CarpenterGameHUD.h"

#include "CarpenterPlayerController.h"
#include "Blueprint/UserWidget.h"
#include "Widget/MoneyWidget.h"
#include "Widget/OrderWidget.h"

void ACarpenterGameHUD::BeginPlay()
{
	Super::BeginPlay();
	
	AddMoneyWidget();
}

void ACarpenterGameHUD::AddOrderWidget(int32 X)
{
	APlayerController *PlayerController = GetOwningPlayerController();
	if(PlayerController && OrderWidget)
	{
		OrderWidgetAccess = CreateWidget<UOrderWidget>(PlayerController, OrderWidget);
		if(OrderWidgetAccess)
		{
			int32 y = (X >> 3) << 3;
			int32 x = X - y;
			OrderWidgetAccess->y = y;
			OrderWidgetAccess->x = x;
			OrderWidgetAccess->setImagesWidget();
			OrderWidgetAccess->AddToViewport();
			
		}
	}
}

void ACarpenterGameHUD::AddMoneyWidget()
{
	APlayerController *PlayerController = GetOwningPlayerController();
	if(PlayerController && MoneyWidget)
	{
		MoneyWidgetAccess = CreateWidget<UMoneyWidget>(PlayerController, MoneyWidget);
		if(MoneyWidgetAccess)
			MoneyWidgetAccess->AddToViewport();
	}
}
