// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/OrderWidget.h"

#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Furnitures/FurnitureSubClass.h"


void UOrderWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
		
}

void UOrderWidget::setImagesWidget()
{
	switch (x)
	{
	case Blue:
		Image1->WidgetStyle.Normal.SetResourceObject(Cast<UObject>(Images.BlueImg));
		break;
	case Green:
		Image1->WidgetStyle.Normal.SetResourceObject(Cast<UObject>(Images.GreenImg));
		break;
	case Red:
		Image1->WidgetStyle.Normal.SetResourceObject(Cast<UObject>(Images.RedImg));
		break;
	default:
		break;
	}
	switch (y)
	{
	case Cylinder:
		Text->SetText(FText::FromString(FString("Silindir")));
		break;
	case Cube:
		Text->SetText(FText::FromString(FString("Kup")));
		break;
	case Cone:
		Text->SetText(FText::FromString(FString("Koni")));
		break;
		default:
		break;
	}
}
