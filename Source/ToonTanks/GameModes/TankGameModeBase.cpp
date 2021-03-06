// Fill out your copyright notice in the Description page of Project Settings.


#include "TankGameModeBase.h"

#include "NetworkMessage.h"
#include "Kismet/GameplayStatics.h"
#include "ToonTanks/Pawns/PawnTank.h"
#include "ToonTanks/Pawns/PawnTurret.h"
#include "ToonTanks/PlayerControllers/PlayerControllerBase.h"
#include "Components/AudioComponent.h"

ATankGameModeBase::ATankGameModeBase()
{
	PrimaryActorTick.bCanEverTick = true;

	Music = CreateDefaultSubobject<UAudioComponent>(TEXT("Main Menu Music"));
}

void ATankGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	HandleGameStart();
}

void ATankGameModeBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if(!PlayerPawn){return;}
	Health = PlayerPawn->GetPlayerHP();
	if(bTimerDone){return;}
	SetTimerForPlayerControll();
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
		Score+=IncrementScoreAmount;
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
	PlayerControllerRef->bShowMouseCursor = true;
}

void ATankGameModeBase::HandleGameOver(bool bPlayerWon)
{
	GameOver(bPlayerWon);
}

bool ATankGameModeBase::GetIsPlaying()
{
	return bPlay;
}

int32 ATankGameModeBase::GetScore()
{
	return Score;
}

void ATankGameModeBase::SetPlayStart()
{
	bPlay = true;
}

void ATankGameModeBase::SetTimerForPlayerControll()
{
	if(bPlay)
	{
		FTimerHandle PlayerEnabledHandle;
		FTimerDelegate PlayerEnableDelegate = FTimerDelegate::CreateUObject(PlayerControllerRef, &APlayerControllerBase::SetPlayerEnabledState, true);
		GetWorld()->GetTimerManager().SetTimer(PlayerEnabledHandle, PlayerEnableDelegate, StartDelay, false);
		bTimerDone = true;
	}
}

bool ATankGameModeBase::GetReadySpawn()
{
	return bReadySpawn;
}

void ATankGameModeBase::SetReadySpawn()
{
	bReadySpawn = true;
}




