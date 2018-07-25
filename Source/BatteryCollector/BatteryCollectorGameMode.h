// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "BatteryCollectorGameMode.generated.h"

UCLASS(minimalapi)
class ABatteryCollectorGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ABatteryCollectorGameMode();

    virtual void BeginPlay() override;

    virtual void Tick(float DeltaTime) override;

    UFUNCTION(BlueprintPure, Category = "Power")
    float GetPowerToWin() const noexcept { return powerToWin; }

protected:

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Power", Meta = (BlueprintProtected = "true"))
    float decayRate;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Power", Meta = (BlueprintProtected = "true"))
    float powerToWin;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Power", Meta = (BlueprintProtected = "true"))
    TSubclassOf<class UUserWidget> HUDWidgetClass;

    UPROPERTY()
    class UUserWidget *currentWidget;
};



