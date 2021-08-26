// Fill out your copyright notice in the Description page of Project Settings.


#include "DestroyableObject.h"
#include "Components/StaticMeshComponent.h"
#include "ToonTanks/Components/HealthComponent.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
ADestroyableObject::ADestroyableObject()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));
    RootComponent = BaseMesh;

    HealthComp = CreateDefaultSubobject<UHealthComponent>(TEXT("Health Component"));
}

// Called when the game starts or when spawned
void ADestroyableObject::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ADestroyableObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	OnDestruction();
}

void ADestroyableObject::OnDestruction()
{
	if(HealthComp->GetHealth() <= 0.f)
	{
		UGameplayStatics::SpawnEmitterAtLocation(this, DeathEffect, GetActorLocation());
		UGameplayStatics::SpawnSoundAtLocation(this, DeathSound, GetActorLocation());
		UGameplayStatics::SpawnSoundAtLocation(this, HitSound, GetActorLocation());
		Destroy();
	}
}