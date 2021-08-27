// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerControllerBase.h"
#include "ToonTanks/GameModes/TankGameModeBase.h"
#include "Kismet/GameplayStatics.h"

void APlayerControllerBase::SetPlayerEnabledState(bool bEnable)
{
	ATankGameModeBase* Gamemode = Cast<ATankGameModeBase>(UGameplayStatics::GetGameMode(this));
	if (bEnable) {
		GetPawn()->EnableInput(this);
		CurrentMouseCursor = EMouseCursor::Crosshairs;
		Gamemode->SetReadySpawn();
	}
	else {
		bShowMouseCursor = false;
		GetPawn()->DisableInput(this);
	}
}
