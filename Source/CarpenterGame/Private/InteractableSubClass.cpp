// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractableSubClass.h"
#include "Components/PrimitiveComponent.h"
#include "CarpenterGame/CarpenterGameCharacter.h"
#include "Components/SphereComponent.h"
#include "Components/WidgetComponent.h"
#include "Net/UnrealNetwork.h"

// Sets default values
AInteractableSubClass::AInteractableSubClass()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	RootComponent = Mesh;
	
	Collision = CreateDefaultSubobject<USphereComponent>(TEXT("SphereCollision"));
	Collision->SetupAttachment(RootComponent);
	Collision->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	Collision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	Collision->SetSphereRadius(53.f);

	PickupWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("PickUpWidget"));
	PickupWidget->SetupAttachment(RootComponent);
	
	

}

void AInteractableSubClass::OnRep_ClassState()
{
	switch (ClassState)
	{
		case EState::Carried:
			SetPickUpWidget(false);
			Collision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
			break;
		case EState::Dropped:
			Collision->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
			//SetPickUpWidget(true);
			break;
		default:
			break;
	}
}

void AInteractableSubClass::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AInteractableSubClass,ClassState);
}

// Called when the game starts or when spawned
void AInteractableSubClass::BeginPlay()
{
	Super::BeginPlay();

	if (HasAuthority())
	{
		Collision->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		Collision->SetCollisionResponseToChannel(ECC_Pawn,ECR_Overlap);
		Collision->OnComponentBeginOverlap.AddUniqueDynamic(this, &AInteractableSubClass::OnSphereOverlap); 
		Collision->OnComponentEndOverlap.AddUniqueDynamic(this, &AInteractableSubClass::OnSphereEndOverlap);
	}
	if(PickupWidget)
	{
		PickupWidget->SetVisibility(false);
	}
	//SetState(EState::Dropped);
}

void AInteractableSubClass::OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ACarpenterGameCharacter* Character = Cast<ACarpenterGameCharacter>(OtherActor);
	if(Character)
	{
		Character->SetOverlapping(this);
	}
}

void AInteractableSubClass::OnSphereEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	ACarpenterGameCharacter* Character = Cast<ACarpenterGameCharacter>(OtherActor);
	if(Character)
	{
		Character->SetOverlapping(nullptr);
	}
}

void AInteractableSubClass::SetState(EState State)
{
	ClassState = State;
}

void AInteractableSubClass::SetPickUpWidget(bool bflag)
{
	PickupWidget->SetVisibility(bflag);
}

// Called every frame
void AInteractableSubClass::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

