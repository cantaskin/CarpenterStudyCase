// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "OrderWidget.generated.h"

/**
 * 
 */
USTRUCT()
struct FImages
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere)
	class UTexture2D* GreenImg;

	UPROPERTY(EditAnywhere)
	class UTexture2D* BlueImg;

	UPROPERTY(EditAnywhere)
	class UTexture2D* RedImg;
};
UCLASS()
class CARPENTERGAME_API UOrderWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	FImages Images;

	UPROPERTY(meta=(BindWidget))
	class UButton* Image1;

	UPROPERTY(meta=(BindWidget))
	class UButton* Image2;

	UPROPERTY(meta=(BindWidget))
	class UTextBlock* Text;
	
	int32 x;
	int32 y;

	virtual void NativeConstruct() override;
	void setImagesWidget();
};
