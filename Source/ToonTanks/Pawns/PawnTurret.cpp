// Fill out your copyright notice in the Description page of Project Settings.


#include "PawnTurret.h"
#include "Kismet/GameplayStatics.h"
#include "PawnTank.h"
#include "ToonTanks/Components/HealthComponent.h"
#include "ToonTanks/Actors/HealthBulb.h"
#include "ToonTanks/GameModes/TankGameModeBase.h"

APawnTurret::APawnTurret()
{
	PrimaryActorTick.bCanEverTick = true;
	
	SpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Spawn Point"));
	SpawnPoint->SetupAttachment(RootComponent);
}

void APawnTurret::BeginPlay()
{
	Super::BeginPlay();
	GetWorldTimerManager().SetTimer(FireRateTimerHandle, this, &APawnTurret::CheckFireCondition, FireRate, true);
	PlayerPawn = Cast<APawnTank>(UGameplayStatics::GetPlayerPawn(this, 0));
	EnemyMoveToTarget();
	GameMode = Cast<ATankGameModeBase>(UGameplayStatics::GetGameMode(this));
}

void APawnTurret::HandleDestruction()
{
	Super::HandleDestruction();
	Randomizer();
	Destroy();
}

void APawnTurret::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(!PlayerPawn)
	{
		return;
	}
	SetupHealthModifier();
	EnemyMoveToTarget();
	RotateTurret(PlayerPawn->GetActorLocation());
}

void APawnTurret::CheckFireCondition()
{
	if (!PlayerPawn || !PlayerPawn->GetIsPlayerAlive()) {
		return;
	}
	if (GetPlayerDistance() <= FireRange) {
		Fire();
	}
}

float APawnTurret::GetPlayerDistance()
{
	if (!PlayerPawn) {
		return 0.f;
	}

	return FVector::Dist(PlayerPawn->GetActorLocation(), GetActorLocation());
}

void APawnTurret::EnemyMoveToTarget()
{
	if(!PlayerPawn){return;}

	FVector EnemyMovementDirection = FVector(-1 * 200.f * GetWorld()->DeltaTimeSeconds, 0, 0);
	FRotator EnemyRotationDirection = FRotator(0, PlayerPawn->GetRotationValue() * 100.f * GetWorld()->DeltaTimeSeconds, 0);
	
	AddActorLocalOffset(EnemyMovementDirection, true);
	AddActorLocalRotation(FQuat(EnemyRotationDirection) , true);
}

void APawnTurret::ModifyHealth()
{
	if(!GameMode){return;}
	if(GameMode->GetScore() == HealthMultiplicityAtScore /*&& !bHealthAdded*/)
	{
		HealthComponent->AddHealth(HealthAdded);
		DropChance += 3;
		HealthMultiplicityAtScore += HealthMultiplicityAtScore;
		bHealthAdded = true;
	}
}

void APawnTurret::SetupHealthModifier()
{
	if(!GameMode){return;}
	if(GameMode->GetScore() != HealthMultiplicityAtScore)
	{
		bHealthAdded = false;
	}
	ModifyHealth();
}

void APawnTurret::Randomizer()
{
	int32 Random = FMath::RandRange(0, DropChance);
	if(Random == 1)
	{
		GetWorld()->SpawnActor<AHealthBulb>(BulbClass, SpawnPoint->GetComponentLocation(), SpawnPoint->GetComponentRotation());
	}
}


