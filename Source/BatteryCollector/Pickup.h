// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Pickup.generated.h"

UCLASS()
class BATTERYCOLLECTOR_API APickup : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APickup();

    UFUNCTION(BlueprintPure, Category = "Pickup")
    bool IsActive();

    UFUNCTION(BlueprintCallable, Category = "Pickup")
    void SetActive(bool pickupState);

    UFUNCTION(BlueprintNativeEvent)
    void WasCollected();

    virtual void WasCollected_Implementation();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

    bool bIsActive;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

    FORCEINLINE class UStaticMeshComponent *GetMesh() const noexcept { return pickupMesh; }

private:

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Pickup", Meta = (AllowPrivateAccess = "true"))
    class UStaticMeshComponent *pickupMesh;
	
};
