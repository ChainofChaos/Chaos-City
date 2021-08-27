// Fill out your copyright notice in the Description page of Project Settings.


#include "DestroyActorOverlapping.h"
#include "Engine/TriggerVolume.h"
#include "ToonTanks/Pawns/PawnTurret.h"

// Sets default values for this component's properties
UDestroyActorOverlapping::UDestroyActorOverlapping()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	TriggerVolume = CreateDefaultSubobject<ATriggerVolume>(TEXT("Trigger Volume"));
}


// Called when the game starts
void UDestroyActorOverlapping::BeginPlay()
{
	Super::BeginPlay();

	FindTriggerVolume();
}


// Called every frame
void UDestroyActorOverlapping::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if(!TriggerVolume){return;}
	DestroyActorInside();
}

void UDestroyActorOverlapping::FindTriggerVolume()
{
	if(!TriggerVolume)
	{
		UE_LOG(LogTemp, Error, TEXT("%s do not have trigger volume"), *GetOwner()->GetName());
	}
}

void UDestroyActorOverlapping::DestroyActorInside()
{
	TArray<AActor*> Turret;
	TriggerVolume->GetOverlappingActors(Turret);
	if(!TriggerVolume){return;}
	for(AActor* Actor : Turret)
	{
		if(Actor->IsA(APawnTurret::StaticClass()))
		{
			Actor->Destroy();
		}
	}
}


