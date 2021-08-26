// Fill out your copyright notice in the Description page of Project Settings.


#include "PawnTurret.h"
#include "AIController.h" 
#include "Kismet/GameplayStatics.h"
#include "PawnTank.h"

void APawnTurret::BeginPlay()
{
	Super::BeginPlay();
	GetWorldTimerManager().SetTimer(FireRateTimerHandle, this, &APawnTurret::CheckFireCondition, FireRate, true);
	PlayerPawn = Cast<APawnTank>(UGameplayStatics::GetPlayerPawn(this, 0));
	EnemyMoveToTarget();
}

void APawnTurret::HandleDestruction()
{
	Super::HandleDestruction();
	Destroy();
}

void APawnTurret::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(!PlayerPawn)
	{
		return;
	}
	EnemyMoveToTarget();
	if (GetPlayerDistance() > FireRange) {
		return;
	}
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
<<<<<<< Updated upstream
	AAIController* AIController = Cast<AAIController>(GetController());
=======
	AEnemyAIController* AIController = Cast<AEnemyAIController>(GetController());
	//sepertinya tidak masuk sini juga
>>>>>>> Stashed changes
	if(!AIController){return;}
	AIController->MoveToActor(PlayerPawn, 5.f, false, true);
	//AIController->MoveToLocation(TargetLocation, 5.f, false);
}