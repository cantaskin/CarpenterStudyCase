// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InteractableSubClass.h"
#include "Final.generated.h"

UCLASS()
class CARPENTERGAME_API AFinal : public AActor
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere)
	class UWidgetComponent* PickupWidget;
	
	UPROPERTY(VisibleAnywhere, Category = "Sphere Collision")
	class USphereComponent* Collision;
	
public:	
	// Sets default values for this actor's properties
	AFinal();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	virtual void OnSphereOverlap(
		UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult
		);
	
	void OnSphereEndOverlap(
		UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex
	);
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
