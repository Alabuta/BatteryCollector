// Fill out your copyright notice in the Description page of Project Settings.

#include "SpawnVolume.h"
#include "Components/BoxComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Engine/World.h"
#include "TimerManager.h"

#include "Pickup.h"



// Sets default values
ASpawnVolume::ASpawnVolume()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

    whereToSpawn = CreateDefaultSubobject<UBoxComponent>(TEXT("WhereToSpawn"));
    SetRootComponent(whereToSpawn);

    spawnDelayRangeLow = 1.f;
    spawnDelayRangeHigh = 4.5f;
}

// Called when the game starts or when spawned
void ASpawnVolume::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ASpawnVolume::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

FVector ASpawnVolume::GetRandomPointInVolume()
{
    auto &&spawnOrigin = whereToSpawn->Bounds.Origin;
    auto &&spwanExtend = whereToSpawn->Bounds.BoxExtent;

    return UKismetMathLibrary::RandomPointInBoundingBox(spawnOrigin, spwanExtend);
}

void ASpawnVolume::SetSpawningActive(bool shouldSpawn)
{
    if (shouldSpawn) {
        spawnDelay = FMath::FRandRange(spawnDelayRangeLow, spawnDelayRangeHigh);
        GetWorldTimerManager().SetTimer(spawnTimer, this, &ASpawnVolume::SpawnPickup, spawnDelay, false);
    }

    else GetWorldTimerManager().ClearTimer(spawnTimer);
}

void ASpawnVolume::SpawnPickup()
{
    if (whatToSpawn) {
        auto const world = GetWorld();

        if (world) {
            FActorSpawnParameters spawnParams;
            spawnParams.Owner = this;
            spawnParams.Instigator = Instigator;

            auto spawnLocation = GetRandomPointInVolume();

            FRotator spawnRotation;
            spawnRotation.Yaw = FMath::FRand() * 360.f;
            spawnRotation.Pitch = FMath::FRand() * 360.f;
            spawnRotation.Roll = FMath::FRand() * 360.f;

            auto spawnedPickup = world->SpawnActor<APickup>(whatToSpawn, spawnLocation, spawnRotation, spawnParams);

            spawnDelay = FMath::FRandRange(spawnDelayRangeLow, spawnDelayRangeHigh);
            GetWorldTimerManager().SetTimer(spawnTimer, this, &ASpawnVolume::SpawnPickup, spawnDelay, false);
        }
    }
}
