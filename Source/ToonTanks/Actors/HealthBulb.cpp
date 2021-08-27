// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthBulb.h"
#include "Components/StaticMeshComponent.h"
#include "ToonTanks/Pawns/PawnTank.h"
#include "Kismet/GameplayStatics.h"
#include "ToonTanks/Components/HealthComponent.h"

// Sets default values
AHealthBulb::AHealthBulb()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));
	RootComponent = BaseMesh;
}

// Called when the game starts or when spawned
void AHealthBulb::BeginPlay()
{
	Super::BeginPlay();
	
	BaseMesh->OnComponentHit.AddDynamic(this, &AHealthBulb::OnHit);
}

// Called every frame
void AHealthBulb::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AHealthBulb::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	AActor* MyOwner = GetOwner();
	if (OtherActor && OtherActor != this && OtherActor != MyOwner && OtherActor->IsA(APawnTank::StaticClass())) {
		APawnTank* PlayerPawn = Cast<APawnTank>(UGameplayStatics::GetPlayerPawn(this, 0));
		PlayerPawn->HealthComponent->Heal(IncrementValue);
		Destroy();
	}
}


