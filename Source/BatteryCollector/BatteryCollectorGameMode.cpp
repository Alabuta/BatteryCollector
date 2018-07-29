// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "BatteryCollectorGameMode.h"
#include "BatteryCollectorCharacter.h"
#include "UObject/ConstructorHelpers.h"

#include "Kismet/GameplayStatics.h"
#include "Blueprint/UserWidget.h"
#include "GameFramework/Character.h"
#include "GameFramework/PawnMovementComponent.h"
#include "Components/SkeletalMeshComponent.h"

#include "SpawnVolume.h"

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

    TArray<AActor *> foundActors;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), ASpawnVolume::StaticClass(), foundActors);

    for (auto actor : foundActors) {
        auto spawnVolumeActor = Cast<ASpawnVolume>(actor);

        if (spawnVolumeActor) {
            spawnVolumeActors.AddUnique(spawnVolumeActor);
        }
    }

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

void ABatteryCollectorGameMode::SetCurrentState(eBatteryPlayState state) noexcept
{
    currentState = state;
    HandleNewState(state);
}

void ABatteryCollectorGameMode::HandleNewState(eBatteryPlayState state)
{
    switch (state) {
        case eBatteryPlayState::nPlaying:
            for (auto spawnVolumeActor : spawnVolumeActors)
                spawnVolumeActor->SetSpawningActive(true);

            break;

        case eBatteryPlayState::nGameOver:
            for (auto spawnVolumeActor : spawnVolumeActors)
                spawnVolumeActor->SetSpawningActive(false);

            {
                auto playerController = UGameplayStatics::GetPlayerController(this, 0);

                if (playerController) {
                    playerController->SetCinematicMode(true, false, false, true, true);
                }

                auto myCharacter = UGameplayStatics::GetPlayerCharacter(this, 0);

                if (myCharacter) {
                    auto mesh = myCharacter->GetMesh();
                    mesh->SetSimulatePhysics(true);

                    auto movementComponent = myCharacter->GetMovementComponent();
                    movementComponent->MovementState.bCanJump = false;
                }
            }

            break;

        case eBatteryPlayState::nWon:
            for (auto spawnVolumeActor : spawnVolumeActors)
                spawnVolumeActor->SetSpawningActive(false);

            break;

        default:
            break;
    }
}

