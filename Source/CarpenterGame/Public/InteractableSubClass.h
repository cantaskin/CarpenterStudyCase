// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InteractableSubClass.generated.h"

UENUM(BlueprintType)
enum class EState : uint8
{
	Dropped,
	Carried
};
UCLASS()
class CARPENTERGAME_API AInteractableSubClass : public AActor
{
	GENERATED_BODY()
	
	UPROPERTY(VisibleAnywhere)
	class UWidgetComponent* PickupWidget;

	UPROPERTY(VisibleAnywhere, Category = "Sphere Collision")
	class USphereComponent* Collision;

	UPROPERTY(ReplicatedUsing= OnRep_ClassState, VisibleAnywhere, Category= "State")
	EState ClassState;
public:	
	// Sets default values for this actor's properties
	AInteractableSubClass();

	UFUNCTION()
	void OnRep_ClassState();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

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

	UFUNCTION()
	void OnSphereEndOverlap(
		UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex
	);

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* Mesh;
	
public:	
	// Called every frame
	FORCEINLINE UStaticMeshComponent* getMesh() const {return Mesh;}
	void SetState(EState State);
	void SetPickUpWidget(bool bflag);
	virtual void Tick(float DeltaTime) override;

};
