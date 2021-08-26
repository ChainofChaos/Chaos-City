// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DestroyableObject.generated.h"


class UHealthComponent;

UCLASS()
class TOONTANKS_API ADestroyableObject : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADestroyableObject();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Component", meta = (AllowPrivateAccess = "true"))	
    UStaticMeshComponent* BaseMesh;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Component", meta = (AllowPrivateAccess = "true"))
    UHealthComponent* HealthComp;

    UPROPERTY(EditAnywhere, Category = "Effect")
    UParticleSystem* DeathEffect;

    UPROPERTY(EditAnywhere, Category = "Effect")
    USoundBase* DeathSound;
    
    UPROPERTY(EditAnywhere, Category = "Effect")
    USoundBase* HitSound;

    void OnDestruction();
};
