// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractableSubClass.h"
#include "GameFramework/Actor.h"
#include "PressingButton.generated.h"

UCLASS()
class CARPENTERGAME_API APressingButton : public AInteractableSubClass
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APressingButton();

	UPROPERTY(EditAnywhere, Category= "Type Index")
	int32 Type;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	FORCEINLINE int32 getType(){return Type;}
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
