// Fill out your copyright notice in the Description page of Project Settings.

#include "SpawnVolume.h"
#include "Components/BoxComponent.h"
#include "Kismet/KismetMathLibrary.h"


// Sets default values
ASpawnVolume::ASpawnVolume()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

    whereToSpawn = CreateDefaultSubobject<UBoxComponent>(TEXT("WhereToSpawn"));
    SetRootComponent(whereToSpawn);
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
