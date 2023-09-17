// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "CarpenterGameState.generated.h"

/**
 * 
 */
UCLASS()
class CARPENTERGAME_API ACarpenterGameState : public AGameStateBase
{
	GENERATED_BODY()

	ACarpenterGameState();
	public:
		virtual  void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UFUNCTION()
	void On_RepMoney();
	
	UPROPERTY(ReplicatedUsing= On_RepMoney)
		int32 Money;

	UPROPERTY(ReplicatedUsing= On_RepTotal)
	int32 Total;

	UFUNCTION()
	void On_RepTotal();
	void SetMoney(int32 Temp);
	void SetNumber();
};
