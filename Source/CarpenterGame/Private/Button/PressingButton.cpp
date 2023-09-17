// Fill out your copyright notice in the Description page of Project Settings.


#include "Button/PressingButton.h"

// Sets default values
APressingButton::APressingButton()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APressingButton::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APressingButton::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

