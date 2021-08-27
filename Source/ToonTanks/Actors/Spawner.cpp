// Fill out your copyright notice in the Description page of Project Settings.


#include "Spawner.h"
#include "Components/StaticMeshComponent.h"
#include "ToonTanks/Pawns/PawnTurret.h"
#include "ToonTanks/GameModes/TankGameModeBase.h"
#include "Kismet/GameplayStatics.h"

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

	GameModeBase = Cast<ATankGameModeBase>(UGameplayStatics::GetGameMode(this));
}

// Called every frame
void ASpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	ModifySpawnerDelay();
	SetSpawnerTimer();
	if(bSpawned == true){return;}
	SpawnEnemy();
}

void ASpawner::SpawnEnemy()
{
	if(!TurretClass || !GameModeBase){return;}
	if(!GameModeBase->GetReadySpawn()){return;}
	GetWorld()->SpawnActor<APawnTurret>(TurretClass, SpawnPoint->GetComponentLocation(), SpawnPoint->GetComponentRotation());
	LastSpawnTime = GetWorld()->GetTimeSeconds();
	bSpawned = true;
}

void ASpawner::SetSpawnerTimer()
{
	if(LastSpawnTime + SpawningDelay <= GetWorld()->GetTimeSeconds() && LastSpawnTime != 0)
	{
		bSpawned = false;
		if(GameModeBase->GetScore() != SpawnerMultiplicityAtScore)
		{
			bDecrementDelay = false;
		}
	}
}

void ASpawner::ModifySpawnerDelay()
{
	if(!GameModeBase){return;}
	if(GameModeBase->GetScore() == SpawnerMultiplicityAtScore && !bDecrementDelay && SpawningDelay >= 2.5f)
	{
		SpawningDelay-=0.5;
		SpawnerMultiplicityAtScore+=SpawnerMultiplicityAtScore;
		bDecrementDelay = true;
	}
}


