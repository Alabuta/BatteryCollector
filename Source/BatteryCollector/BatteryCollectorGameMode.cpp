// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "BatteryCollectorGameMode.h"
#include "BatteryCollectorCharacter.h"
#include "UObject/ConstructorHelpers.h"

#include "Kismet/GameplayStatics.h"
#include "Blueprint/UserWidget.h"

ABatteryCollectorGameMode::ABatteryCollectorGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

    decayRate = .1f;

    PrimaryActorTick.bCanEverTick = true;
}

void ABatteryCollectorGameMode::BeginPlay()
{
    Super::BeginPlay();

    SetCurrentState(eBatteryPlayState::nPlaying);

    auto myCharacter = Cast<ABatteryCollectorCharacter>(UGameplayStatics::GetPlayerPawn(this, 0));

    if (myCharacter)
        powerToWin = myCharacter->GetInitialPower() * 1.25f;

    if (HUDWidgetClass) {
        currentWidget = CreateWidget<UUserWidget>(GetWorld(), HUDWidgetClass);

        if (currentWidget)
            currentWidget->AddToViewport();
    }
}

void ABatteryCollectorGameMode::Tick(float deltaTime)
{
    Super::Tick(deltaTime);

    auto myCharacter = Cast<ABatteryCollectorCharacter>(UGameplayStatics::GetPlayerPawn(this, 0));

    if (myCharacter) {
        if (myCharacter->GetCurrentPower() > powerToWin)
            SetCurrentState(eBatteryPlayState::nWon);

        else if (myCharacter->GetCurrentPower() > 0)
            myCharacter->UpdatePower(-deltaTime * decayRate * myCharacter->GetInitialPower());

        else SetCurrentState(eBatteryPlayState::nGameOver);
    }
}
