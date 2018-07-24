// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "BatteryCollectorGameMode.h"
#include "BatteryCollectorCharacter.h"
#include "UObject/ConstructorHelpers.h"

#include "Kismet/GameplayStatics.h"

ABatteryCollectorGameMode::ABatteryCollectorGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

    decayRate = .01f;
}

void ABatteryCollectorGameMode::Tick(float deltaTime)
{
    Super::Tick(deltaTime);

    auto myCharacter = Cast<ABatteryCollectorCharacter>(UGameplayStatics::GetPlayerPawn(this, 0));
    UE_LOG(LogClass, Log, TEXT("!!!!!!!!!!!!!!"))

    if (myCharacter)
        if (myCharacter->GetCurrentPower() > 0)
            myCharacter->UpdatePower(-deltaTime * decayRate * myCharacter->GetInitialPower());
}
