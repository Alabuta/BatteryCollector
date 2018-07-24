// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpawnVolume.generated.h"

UCLASS()
class BATTERYCOLLECTOR_API ASpawnVolume : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
    ASpawnVolume();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

    FORCEINLINE class UBoxComponent *GetWhereToSpawn() const noexcept { return whereToSpawn; }

    UFUNCTION(BlueprintPure, Category = "Spawning")
    FVector GetRandomPointInVolume();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

    UPROPERTY(EditAnywhere, Category = "Spawning")
    TSubclassOf<class APickup> whatToSpawn;

    FTimerHandle spawnTimer;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawning")
    float spawnDelayRangeLow;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawning")
    float spawnDelayRangeHigh;

private:

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Spawning", Meta = (AllowPrivateAccess = "true"))
    class UBoxComponent *whereToSpawn;

    void SpawnPickup();
	
    float spawnDelay{1.f};
};
