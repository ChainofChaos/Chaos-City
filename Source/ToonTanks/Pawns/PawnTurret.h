// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PawnBase.h"
#include "PawnTurret.generated.h"

class APawnTank;
class AAIController;

UCLASS()
class TOONTANKS_API APawnTurret : public APawnBase
{
	GENERATED_BODY()
	
public:

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void HandleDestruction() override;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Combat", meta = (AllowPrivateAccess = "true"))
	float FireRate = 2.f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Combat", meta = (AllowPrivateAccess = "true"))
	float FireRange = 500.f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Combat", meta = (AllowPrivateAccess = "true"))
	float MovementSpeed = 100.f;
	FTimerHandle FireRateTimerHandle;
	APawnTank* PlayerPawn;
	AAIController* Controller;
	FVector MoveDirection;

	void CheckFireCondition();
	void MoveToTarget(FVector TargetLocation, float Speed);
	float GetPlayerDistance();
};
