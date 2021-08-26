// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TankGameModeBase.generated.h"

class APawnTank;
class APawnTurret;
class APlayerControllerBase;
UCLASS()
class TOONTANKS_API ATankGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	void ActorDied(AActor* DeadActor);
	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly, Category = "Game Loop")
	int32 StartDelay = 4;

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly, Category = "Combat")
	int32 IncrementScoreAmount = 10;

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly, Category = "Combat")
	int32 Score = 0;

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly, Category = "Combat")
	int32 Health = 0;
	
	virtual void BeginPlay() override;
	UFUNCTION(BlueprintImplementableEvent)
	void GameStart();
	UFUNCTION(BlueprintImplementableEvent)
	void UILoad();
	UFUNCTION(BlueprintImplementableEvent)
	void GameOver(bool bPlayerWon);

private:
	APawnTank* PlayerPawn;
	APlayerControllerBase* PlayerControllerRef;
	int32 TargetTurret;

	void HandleGameStart();
	void HandleGameOver(bool bPlayerWon);

};
