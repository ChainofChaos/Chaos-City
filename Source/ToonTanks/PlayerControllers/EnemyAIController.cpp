// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyAIController.h"
#include "ToonTanks/Pawns/PawnTurret.h"

void AEnemyAIController::OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result)
{
	APawnTurret* Turret = Cast<APawnTurret>(APawnTurret::StaticClass());
	if(!Turret)
	{
		return;
	}
	UE_LOG(LogTemp, Warning, TEXT("A"));
	//tidak masuk sini brt kemungkinan castnya salah
	Turret->EnemyMoveToTarget();	
}

