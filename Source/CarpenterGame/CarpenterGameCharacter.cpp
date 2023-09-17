// Copyright Epic Games, Inc. All Rights Reserved.

#include "CarpenterGameCharacter.h"

#include "CarpenterPlayerController.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Button/PressingButton.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "Engine/SkeletalMeshSocket.h"
#include "Furnitures/FurnitureSubClass.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameHud/CarpenterGameHUD.h"
#include "GameState/CarpenterGameState.h"
#include "Net/UnrealNetwork.h"
#include "Spawner/Spawner.h"
#include "Widget/MoneyWidget.h"

//////////////////////////////////////////////////////////////////////////
// ACarpenterGameCharacter

void ACarpenterGameCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ACarpenterGameCharacter,EquippedActor);
	DOREPLIFETIME_CONDITION(ACarpenterGameCharacter,OverlayActor, COND_OwnerOnly);
	DOREPLIFETIME(ACarpenterGameCharacter,bPickUp);
	DOREPLIFETIME(ACarpenterGameCharacter,Type);
}

void ACarpenterGameCharacter::Server_EquipActor_Implementation()
{
	EquipActor();
}

void ACarpenterGameCharacter::EquipActor()
{
	EquippedActor = OverlayActor;
	if(EquippedActor)
	{
		const USkeletalMeshSocket* HandSocket = GetMesh()->GetSocketByName(FName("hand_rSocket"));
		if(HandSocket)
		{
			//EquippedActor->getMesh()->SetSimulatePhysics(false);
			//EquippedActor->getMesh()->SetCollisionResponseToAllChannels(ECR_Overlap);
			HandSocket->AttachActor(EquippedActor,GetMesh());
		}
		//EquippedActor->SetOwner(this);
		EquippedActor->SetState(EState::Carried);
		EquippedActor->SetPickUpWidget(false);
		//GetCharacterMovement()->bOrientRotationToMovement = false;
		//bUseControllerRotationYaw = true;
		OverlayActor = nullptr;
		bPickUp = true;
	}
	//Socket atama yapa
	
}

void ACarpenterGameCharacter::SetOverlapping(AInteractableSubClass* InteractableActor)
{
	if(OverlayActor)
		OverlayActor->SetPickUpWidget(false);
	OverlayActor = InteractableActor;
	if(IsLocallyControlled() && OverlayActor)
		OverlayActor->SetPickUpWidget(true);
}

ACarpenterGameCharacter::ACarpenterGameCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 300.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm
	
	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named MyCharacter (to avoid direct content references in C++)
}

//////////////////////////////////////////////////////////////////////////
// Input

void ACarpenterGameCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up gameplay key bindings
	check(PlayerInputComponent);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	PlayerInputComponent->BindAction("Spawn", IE_Pressed, this, &ACarpenterGameCharacter::SpawnFurniture);

	PlayerInputComponent->BindAxis("MoveForward", this, &ACarpenterGameCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ACarpenterGameCharacter::MoveRight);

	PlayerInputComponent->BindAction("Interact", IE_Pressed, this, &ACarpenterGameCharacter::Interact);
	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &ACarpenterGameCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &ACarpenterGameCharacter::LookUpAtRate);

	// handle touch devices
	PlayerInputComponent->BindTouch(IE_Pressed, this, &ACarpenterGameCharacter::TouchStarted);
	PlayerInputComponent->BindTouch(IE_Released, this, &ACarpenterGameCharacter::TouchStopped);

	// VR headset functionality
	PlayerInputComponent->BindAction("ResetVR", IE_Pressed, this, &ACarpenterGameCharacter::OnResetVR);
}

void ACarpenterGameCharacter::BeginPlay()
{
	Super::BeginPlay();
	CarpenterController = Cast<ACarpenterPlayerController>(GetController());
	CarpenterGameState = GetWorld()->GetGameState<ACarpenterGameState>();

	
	CarpenterGameState->SetNumber();
	
}

void ACarpenterGameCharacter::On_RepEquipActor()
{
	if(EquippedActor)
	{
		GetCharacterMovement()->bOrientRotationToMovement = false;
		bUseControllerRotationYaw = true;
	}
}

void ACarpenterGameCharacter::On_RepType()
{
	if(OverlayActor)
		OverlayActor->SetPickUpWidget(false);
}


void ACarpenterGameCharacter::On_RepOverlapActor(AInteractableSubClass* InteractableActor)
{
	if(OverlayActor)
		OverlayActor->SetPickUpWidget(true);
	if(InteractableActor)
		InteractableActor->SetPickUpWidget(false);
}


void ACarpenterGameCharacter::Server_SpawnFurniture_Implementation()
{
	SpawnFurniture();
}

void ACarpenterGameCharacter::SpawnFurniture()
{
	if(HasAuthority())
	{
		AFurnitureSubClass *Furniture = nullptr;
		if(OverlayActor)
			OverlayActor->SetPickUpWidget(false);
		if(Type & ETypeAndColour::Cylinder)
			 Furniture = GetWorld()->SpawnActor<AFurnitureSubClass>(Cylinder,FVector(-550.0f,170.0f,250.8f), FRotator::ZeroRotator);
		else if (Type & ETypeAndColour::Cube)
			Furniture = GetWorld()->SpawnActor<AFurnitureSubClass>(Cube,FVector(-550.0f,170.0f,250.8f), FRotator::ZeroRotator);
		else if(Type & ETypeAndColour::Cone)
			Furniture = GetWorld()->SpawnActor<AFurnitureSubClass>(Cone,FVector(-550.0f,170.0f,250.8f), FRotator::ZeroRotator);
		if(CarpenterGameState && Type >= 8)
			CarpenterGameState->SetMoney(CarpenterGameState->Money - 20);
		if(Furniture)
			Furniture->TotalTypes = Type;
	}
	else
		Server_SpawnFurniture();
}

void ACarpenterGameCharacter::OnResetVR()
{
	// If CarpenterGame is added to a project via 'Add Feature' in the Unreal Editor the dependency on HeadMountedDisplay in CarpenterGame.Build.cs is not automatically propagated
	// and a linker error will result.
	// You will need to either:
	//		Add "HeadMountedDisplay" to [YourProject].Build.cs PublicDependencyModuleNames in order to build successfully (appropriate if supporting VR).
	// or:
	//		Comment or delete the call to ResetOrientationAndPosition below (appropriate if not supporting VR)
	UHeadMountedDisplayFunctionLibrary::ResetOrientationAndPosition();
}

void ACarpenterGameCharacter::TouchStarted(ETouchIndex::Type FingerIndex, FVector Location)
{
		Jump();
}

void ACarpenterGameCharacter::TouchStopped(ETouchIndex::Type FingerIndex, FVector Location)
{
		StopJumping();
}

void ACarpenterGameCharacter::Server_DropActor_Implementation()
{
	DropActor();
}

void ACarpenterGameCharacter::DropActor()
{
	if(EquippedActor)
	{
		const USkeletalMeshSocket* HandSocket = GetMesh()->GetSocketByName(FName("hand_rSocket"));
		if(HandSocket)
		{
			EquippedActor->DetachFromActor(FDetachmentTransformRules::KeepRelativeTransform);
			EquippedActor->TeleportTo(GetActorLocation() + GetActorForwardVector() * 50.0f ,FRotator::ZeroRotator);
			EquippedActor->SetState(EState::Dropped);
			EquippedActor = nullptr;
			bPickUp = false;
		}
	}
}
void ACarpenterGameCharacter::PickAndDrop()
{
	if(!bPickUp)
	{
		if(HasAuthority())
			EquipActor();
		else
			Server_EquipActor();
	}
	else
	{
		if(HasAuthority())
			DropActor();
		else
			Server_DropActor();
	}
}

void ACarpenterGameCharacter::Server_ChooseType_Implementation()
{
	ChooseType();
}

void ACarpenterGameCharacter::ChooseType()
{
	if(HasAuthority())
	{
		if(OverlayActor)
		{
			const auto PressButton = Cast<APressingButton>(OverlayActor);
			OverlayActor->SetPickUpWidget(false);
			if(EquippedActor && PressButton && PressButton->getType() <= Red)
			{
				const auto Furniture= Cast<AFurnitureSubClass>(EquippedActor);
				if(Furniture)
				{
					Furniture->addType(PressButton->getType());
					Furniture->ChangeColor();
					Type = None;
				}
			}
			else if(PressButton && PressButton->getType() > Red)
			{
				Type = PressButton->getType();
				PressButton->SetPickUpWidget(false);
			}
		}	
	}
	else
		Server_ChooseType();
}
void ACarpenterGameCharacter::Interact()
{
	if(Cast<APressingButton>(OverlayActor))
		ChooseType();
	else if(Cast<AFurnitureSubClass>(OverlayActor) || EquippedActor)
		PickAndDrop();
	else if(Cast<ASpawner>(OverlayActor))
		SpawnFurniture();
}

void ACarpenterGameCharacter::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void ACarpenterGameCharacter::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void ACarpenterGameCharacter::MoveForward(float Value)
{
	if ((Controller != nullptr) && (Value != 0.0f))
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void ACarpenterGameCharacter::MoveRight(float Value)
{
	if ( (Controller != nullptr) && (Value != 0.0f) )
	{
		// find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
	
		// get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// add movement in that direction
		AddMovementInput(Direction, Value);
	}
}
