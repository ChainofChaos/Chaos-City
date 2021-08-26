// Fill out your copyright notice in the Description page of Project Settings.


#include "Spawner.h"
#include "Components/StaticMeshComponent.h"
#include "ToonTanks/Pawns/PawnTurret.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
ASpawner::ASpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));
	RootComponent = BaseMesh;

	SpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Spawn Point"));
	SpawnPoint->SetupAttachment(RootComponent);

	RootComponent->SetHiddenInGame(true);
}

// Called when the game starts or when spawned
void ASpawner::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	SetSpawnerTimer();
	if(bSpawned == true){return;}
	SpawnEnemy();
}

void ASpawner::SpawnEnemy()
{
	if(!TurretClass){return;}
	GetWorld()->SpawnActor<APawnTurret>(TurretClass, SpawnPoint->GetComponentLocation(), SpawnPoint->GetComponentRotation());
	LastSpawnTime = GetWorld()->GetTimeSeconds();
	bSpawned = true;
}

void ASpawner::SetSpawnerTimer()
{
	if(LastSpawnTime + SpawningDelay <= GetWorld()->GetTimeSeconds() && LastSpawnTime != 0)
	{
		bSpawned = false;
	}
}


