// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractableSubClass.h"
#include "GameFramework/Actor.h"
#include "FurnitureSubClass.generated.h"

UENUM(BlueprintType, meta = (Bitflags, UseEnumValuesAsMaskValuesInEditor = "true"))
enum  ETypeAndColour
{
	None = 0 UMETA(Hidden),
	Blue = 1 << 0,
	Green = 1 << 1,
	Red = 1 << 2,
	Cylinder = 1 << 3 ,
	Cube =  1 << 4,
	Cone = 1 << 5
};
UCLASS()
class CARPENTERGAME_API AFurnitureSubClass : public AInteractableSubClass
{
	GENERATED_BODY()

public:
	UFUNCTION()
	void OnRep_Types();
	
	UPROPERTY(ReplicatedUsing= OnRep_Types, EditAnywhere, Category = "TotalTypes" ) //Replicated
	int32 TotalTypes;
	// Sets default values for this actor's properties
	AFurnitureSubClass();
	// Called every frame

	UFUNCTION(Server, Reliable)
	void Server_ChangeColor();
	
	void ChangeColor();
	void addType(int32 Add);
	virtual void Tick(float DeltaTime) override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	
	UPROPERTY(Replicated, VisibleAnywhere)
	UMaterialInstanceDynamic* DynamicMaterial;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
