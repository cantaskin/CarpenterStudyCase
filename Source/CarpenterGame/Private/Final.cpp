// Fill out your copyright notice in the Description page of Project Settings.


#include "Final.h"

#include "CarpenterGame/CarpenterGameCharacter.h"
#include "Components/SphereComponent.h"
#include "Components/WidgetComponent.h"
#include "Furnitures/FurnitureSubClass.h"
#include "GameState/CarpenterGameState.h"

// Sets default values
AFinal::AFinal()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Collision = CreateDefaultSubobject<USphereComponent>(TEXT("SphereCollision"));
	Collision->SetupAttachment(RootComponent);
	Collision->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	Collision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	Collision->SetSphereRadius(53.f);

	PickupWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("PickUpWidget"));
	PickupWidget->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void AFinal::BeginPlay()
{
	Super::BeginPlay();

	if (HasAuthority())
	{
		Collision->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		Collision->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);
		Collision->OnComponentBeginOverlap.AddDynamic(this, &AFinal::OnSphereOverlap); 
		Collision->OnComponentEndOverlap.AddDynamic(this, &AFinal::OnSphereEndOverlap);
	}
	
}

void AFinal::OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	
	ACarpenterGameCharacter *Character = Cast<ACarpenterGameCharacter>(OtherActor);
	if(Character && Character->getEquippedActor())
	{
		auto Furniture = Cast<AFurnitureSubClass>(Character->getEquippedActor());
		if(Furniture && Character->CarpenterGameState)
		{
			if(Furniture->TotalTypes == Character->CarpenterGameState->Total)
				Character->CarpenterGameState->SetMoney(Character->CarpenterGameState->Money + 30);
			else if(Furniture->TotalTypes & (Character->CarpenterGameState->Total >> 3) << 3) 
				Character->CarpenterGameState->SetMoney(Character->CarpenterGameState->Money + 15);
			Character->DropActor();
				Furniture->Destroy();
			Character->CarpenterGameState->SetNumber();
		}
	}
}

void AFinal::OnSphereEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	
}

// Called every frame
void AFinal::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

