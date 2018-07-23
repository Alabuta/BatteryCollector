// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Pickup.h"
#include "BatteryPickup.generated.h"

/**
 * 
 */
UCLASS()
class BATTERYCOLLECTOR_API ABatteryPickup : public APickup
{
    GENERATED_BODY()

protected:

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Power"/*, meta = (BlueprintProtected = "true")*/)
    float batteryPower;

public:

    ABatteryPickup();

    void WasCollected_Implementation() override;
	
    float GetBatteryPower() const noexcept { return batteryPower; }
	
};
