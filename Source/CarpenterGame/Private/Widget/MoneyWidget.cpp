// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/MoneyWidget.h"

#include "Components/TextBlock.h"

void UMoneyWidget::NativeConstruct()
{
	Super::NativeConstruct();
	const FString Money = "Money : 100";
	MoneyText->SetText(FText::FromString(Money));
}

void UMoneyWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
}

void UMoneyWidget::setMoneyText(int32 Text)
{
	const FString Money = "Money :" + FString::FromInt(Text);
	MoneyText->SetText(FText::FromString(Money));
}
