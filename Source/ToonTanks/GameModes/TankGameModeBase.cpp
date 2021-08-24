// Fill out your copyright notice in the Description page of Project Settings.


#include "TankGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "ToonTanks/Pawns/PawnTank.h"
#include "ToonTanks/Pawns/PawnTurret.h"
#include "ToonTanks/PlayerControllers/PlayerControllerBase.h"


void ATankGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	HandleGameStart();
}

void ATankGameModeBase::ActorDied(AActor* DeadActor)
{
	if (DeadActor == PlayerPawn) {
		PlayerPawn->HandleDestruction();
		HandleGameOver(false);
		PlayerControllerRef->SetPlayerEnabledState(false);
	}
	else if (APawnTurret* DestroyedTurret = Cast<APawnTurret>(DeadActor)) {
		DestroyedTurret->HandleDestruction();
		if (--TargetTurret == 0) {
			HandleGameOver(true);
		}
	}
}


void ATankGameModeBase::HandleGameStart()
{
	TArray<AActor*> TurretActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APawnTurret::StaticClass(), TurretActors);
	TargetTurret = TurretActors.Num();
	PlayerPawn = Cast<APawnTank>(UGameplayStatics::GetPlayerPawn(this, 0));
	PlayerControllerRef = Cast<APlayerControllerBase>(UGameplayStatics::GetPlayerController(this, 0));
	GameStart();
	PlayerControllerRef->SetPlayerEnabledState(false);
	FTimerHandle PlayerEnabledHandle;
	FTimerDelegate PlayerEnableDelegate = FTimerDelegate::CreateUObject(PlayerControllerRef, &APlayerControllerBase::SetPlayerEnabledState, true);
	GetWorld()->GetTimerManager().SetTimer(PlayerEnabledHandle, PlayerEnableDelegate, StartDelay, false);
}

void ATankGameModeBase::HandleGameOver(bool bPlayerWon)
{
	GameOver(bPlayerWon);
}
