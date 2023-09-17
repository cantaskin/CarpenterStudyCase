// Fill out your copyright notice in the Description page of Project Settings.


#include "GameState/CarpenterGameState.h"

#include "CarpenterPlayerController.h"
#include "GameHud/CarpenterGameHUD.h"
#include "Net/UnrealNetwork.h"
#include "Widget/MoneyWidget.h"
#include "Widget/OrderWidget.h"


ACarpenterGameState::ACarpenterGameState()
{
	Money = 100;
}

void ACarpenterGameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ACarpenterGameState,Money);
	DOREPLIFETIME(ACarpenterGameState,Total);
}

void ACarpenterGameState::On_RepMoney()
{
	ACarpenterPlayerController* CarpenterController = Cast<ACarpenterPlayerController>(GetWorld()->GetFirstPlayerController());
	if(CarpenterController && CarpenterController->GameHUD && CarpenterController->GameHUD->MoneyWidgetAccess)
		CarpenterController->GameHUD->MoneyWidgetAccess->setMoneyText(Money);
}

void ACarpenterGameState::On_RepTotal()
{
	ACarpenterPlayerController* CarpenterController = Cast<ACarpenterPlayerController>(GetWorld()->GetFirstPlayerController());
	if(CarpenterController && CarpenterController->GameHUD)
		CarpenterController->GameHUD->AddOrderWidget(Total);
	
}

void ACarpenterGameState::SetMoney(int32 New)
{
	if(HasAuthority())
	{
		Money = New;
		ACarpenterPlayerController* CarpenterController = Cast<ACarpenterPlayerController>(GetWorld()->GetFirstPlayerController());
		if(CarpenterController && CarpenterController->GameHUD && CarpenterController->GameHUD->MoneyWidgetAccess)
			CarpenterController->GameHUD->MoneyWidgetAccess->setMoneyText(Money);
	}
}

void ACarpenterGameState::SetNumber()
{
	if(HasAuthority())
	{
		TArray<int32> Number1 = {1,2,4};
		TArray<int32> Number2 = {8,16,32};
		int32 x = FMath::RandRange(0,2);
		int32 y = FMath::RandRange(0,2);
		Total = Number1[x] + Number2[y];
		ACarpenterPlayerController* CarpenterController = Cast<ACarpenterPlayerController>(GetWorld()->GetFirstPlayerController());
		if(CarpenterController && CarpenterController->GameHUD)
			CarpenterController->GameHUD->AddOrderWidget(Total);
		
	}
}
