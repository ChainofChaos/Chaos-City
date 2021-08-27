// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerControllerBase.h"

void APlayerControllerBase::SetPlayerEnabledState(bool bEnable)
{
	if (bEnable) {
		GetPawn()->EnableInput(this);
		CurrentMouseCursor = EMouseCursor::Crosshairs;
	}
	else {
		bShowMouseCursor = false;
		GetPawn()->DisableInput(this);
	}
}
