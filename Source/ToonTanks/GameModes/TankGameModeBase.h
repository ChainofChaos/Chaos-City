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
	ATankGameModeBase();
	void ActorDied(AActor* DeadActor);
	virtual void Tick(float DeltaTime) override;

	bool GetIsPlaying();
	void SetPlayStart();
	int32 GetScore();
	
	UPROPERTY(EditAnywhere, Category = "Music")
    UAudioComponent* Music;

protected:
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly, Category = "Game Loop")
	int32 StartDelay = 4;

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite, Category = "Combat")
	int32 IncrementScoreAmount = 10;

	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "Combat")
	int32 Score = 0;

	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category = "Combat")
	int32 Health = 0;

	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "Combat")
	bool bPlay = false;
	
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
	bool bTimerDone = false;

	void HandleGameStart();
	void SetTimerForPlayerControll();
	void HandleGameOver(bool bPlayerWon);
};
