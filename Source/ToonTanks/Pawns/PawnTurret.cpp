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
	EnemyMoveToTarget(PlayerPawn->GetActorLocation(), MovementSpeed);
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

void APawnTurret::EnemyMoveToTarget(FVector TargetLocation, float Speed)
{
	AAIController* AIController = Cast<AAIController>(GetController());
	if(!AIController){return;}
	AIController->MoveToLocation(TargetLocation, 5.f, false);
}