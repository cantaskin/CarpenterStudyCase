// Fill out your copyright notice in the Description page of Project Settings.


#include "Furnitures/FurnitureSubClass.h"

#include "Net/UnrealNetwork.h"

// Sets default values
AFurnitureSubClass::AFurnitureSubClass()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;
	
}

void AFurnitureSubClass::Server_ChangeColor_Implementation()
{
	ChangeColor();
}

void AFurnitureSubClass::ChangeColor()
{
	if(HasAuthority())
	{
		if(TotalTypes & Red)
			DynamicMaterial->SetVectorParameterValue(FName("Color"),FLinearColor::Red);
		else if(TotalTypes & Green)
			DynamicMaterial->SetVectorParameterValue(FName("Color"), FLinearColor::Green);
		else if(TotalTypes & Blue)
			DynamicMaterial->SetVectorParameterValue(FName("Color"),FLinearColor::Blue);
	}
	else
		Server_ChangeColor();
}

void AFurnitureSubClass::addType(int32 Add)
{
	if(TotalTypes & Red)
		TotalTypes -= Red;
	else if(TotalTypes & Blue)
		TotalTypes -= Blue;
	else if(TotalTypes & Green)
		TotalTypes -= Green;
	TotalTypes |= Add;
}


// Called when the game starts or when spawned
void AFurnitureSubClass::BeginPlay()
{
	Super::BeginPlay();

	DynamicMaterial = UMaterialInstanceDynamic::Create(Mesh->GetMaterial(0), this);
	Mesh->SetMaterial(0,DynamicMaterial);
	
}

void AFurnitureSubClass::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	
	DOREPLIFETIME(AFurnitureSubClass,TotalTypes);
	DOREPLIFETIME(AFurnitureSubClass,DynamicMaterial);
}

// TotalTypesın ilk kısmı koni falan zaten default olarak değiştir, rengi de totaltypes ile karakterde değiştir onrepe yansıyıp burada değişecek zaten

void AFurnitureSubClass::OnRep_Types()
{
	if(TotalTypes & Red)
		DynamicMaterial->SetVectorParameterValue(FName("Color"),FLinearColor::Red);
	else if(TotalTypes & Green)
		DynamicMaterial->SetVectorParameterValue(FName("Color"), FLinearColor::Green);
	else if(TotalTypes & Blue)
		DynamicMaterial->SetVectorParameterValue(FName("Color"),FLinearColor::Blue);
	}

// Called every frame
void AFurnitureSubClass::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

