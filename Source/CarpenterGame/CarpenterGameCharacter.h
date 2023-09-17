// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CarpenterGameCharacter.generated.h"



UCLASS(config=Game)
class ACarpenterGameCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;
	
	UPROPERTY(ReplicatedUsing= On_RepEquipActor)
	class AInteractableSubClass* EquippedActor;

	UPROPERTY(ReplicatedUsing= On_RepOverlapActor)
	AInteractableSubClass* OverlayActor;

	UPROPERTY(Replicated)
	bool bPickUp = false;

	UPROPERTY()
	class ACarpenterPlayerController * CarpenterController;

	UPROPERTY(ReplicatedUsing= On_RepType)
	int32 Type;
	
public:
	UFUNCTION(Server,Reliable)
	void Server_ChooseType();
	UFUNCTION()
	void On_RepEquipActor();

	UFUNCTION()
	void On_RepType();
	
	UFUNCTION()
	void On_RepOverlapActor(AInteractableSubClass* InteractableActor);
	
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UFUNCTION(Server,Reliable)
	void Server_EquipActor();
	
	void EquipActor();
	void SetOverlapping(AInteractableSubClass* InteractableActor);
	
	ACarpenterGameCharacter();

	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseLookUpRate;

	FORCEINLINE AInteractableSubClass* getEquippedActor() const {return  EquippedActor;}

protected:

	UPROPERTY(EditAnywhere)
	TSubclassOf<class AFurnitureSubClass> Cone;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class AFurnitureSubClass> Cylinder;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class AFurnitureSubClass> Cube;

	virtual void BeginPlay() override;
	
	UFUNCTION(Server, Reliable)
	void Server_DropActor();
	
	UFUNCTION(Server, Reliable)
	void Server_SpawnFurniture();
	
	void SpawnFurniture();

	/** Resets HMD orientation in VR. */
	void OnResetVR();

	/** Called for forwards/backward input */
	void MoveForward(float Value);

	/** Called for side to side input */
	void MoveRight(float Value);

	/** 
	 * Called via input to turn at a given rate. 
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void TurnAtRate(float Rate);

	/**
	 * Called via input to turn look up/down at a given rate. 
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void LookUpAtRate(float Rate);

	/** Handler for when a touch input begins. */
	void TouchStarted(ETouchIndex::Type FingerIndex, FVector Location);

	/** Handler for when a touch input stops. */
	void TouchStopped(ETouchIndex::Type FingerIndex, FVector Location);
	
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	// End of APawn interface

public:
	void DropActor();
	void PickAndDrop();
	void ChooseType();
	void Interact();
	UPROPERTY()
	class ACarpenterGameState *CarpenterGameState;
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }
};

