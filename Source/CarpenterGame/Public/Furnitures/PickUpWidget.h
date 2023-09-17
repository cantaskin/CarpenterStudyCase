// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PickUpWidget.generated.h"

/**
 * 
 */
UCLASS()
class CARPENTERGAME_API UPickUpWidget : public UUserWidget
{
	GENERATED_BODY()

	UPROPERTY(meta =(BindWidget))
	class UTextBlock* Text;

public:
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	
};
