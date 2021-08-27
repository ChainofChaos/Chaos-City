// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PawnBase.h"
#include "ToonTanks/GameModes/TankGameModeBase.h"
#include "PawnTurret.generated.h"

class APawnTank;
class ATankGameModeBase;
class AHealthBulb;

UCLASS()
class TOONTANKS_API APawnTurret : public APawnBase
{
	GENERATED_BODY()
	
public:
	APawnTurret();
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void HandleDestruction() override;
	void EnemyMoveToTarget();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Component", meta = (AllowPrivateAccess = "true"))	
	USceneComponent* SpawnPoint;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Combat", meta = (AllowPrivateAccess = "true"))
	float FireRate = 2.f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Combat", meta = (AllowPrivateAccess = "true"))
	float FireRange = 500.f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Combat", meta = (AllowPrivateAccess = "true"))
	float MovementSpeed = 100.f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Component", meta = (AllowPrivateAccess = "true"))
	int32 HealthMultiplicityAtScore = 50;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Component", meta = (AllowPrivateAccess = "true"))
	int32 HealthAdded = 20;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Component", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<AHealthBulb> BulbClass;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Component", meta = (AllowPrivateAccess = "true"))
	int32 DropChance = 5;
	
	bool bHealthAdded = false;
	FTimerHandle FireRateTimerHandle;
	APawnTank* PlayerPawn;

	ATankGameModeBase* GameMode;
	
	void CheckFireCondition();
	float GetPlayerDistance();
	void ModifyHealth();
	void SetupHealthModifier();
	void Randomizer();
};
