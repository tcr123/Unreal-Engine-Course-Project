// Fill out your copyright notice in the Description page of Project Settings.


#include "KillEmAllGameModeBase.h"
#include "EngineUtils.h"
#include "GameFramework/Controller.h"
#include "ShooterAIController.h"


void AKillEmAllGameModeBase::PawnKilled(APawn* PawnKilled) 
{
    Super::PawnKilled(PawnKilled);

    UE_LOG(LogTemp, Warning, TEXT("A Pawn Has Been Killed"));

    APlayerController* PlayerController = Cast<APlayerController>(PawnKilled->GetController());

    if(PlayerController!=nullptr)
    {
        EndGame(false);
    }

    for(AShooterAIController* AIController: TActorRange<AShooterAIController>(GetWorld()))
    {
        if(!AIController->isDead())
            return;
    }

    EndGame(true);
}

void AKillEmAllGameModeBase::EndGame(bool isPlayerWin) 
{
    for(AController* Controller: TActorRange<AController>(GetWorld()))
    {
        bool Player = Controller->IsPlayerController() == isPlayerWin;
        Controller->GameHasEnded(Controller->GetPawn(), Player);
    }
}
