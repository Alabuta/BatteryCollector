// Fill out your copyright notice in the Description page of Project Settings.

#include "BatteryPickup.h"
#include "GameFramework/Character.h"


ABatteryPickup::ABatteryPickup()
{
    GetMesh()->SetSimulatePhysics(true);

    batteryPower = 150.f;
}

void ABatteryPickup::WasCollected_Implementation()
{
    Super::WasCollected_Implementation();

    Destroy();
}
