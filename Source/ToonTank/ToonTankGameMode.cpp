// Fill out your copyright notice in the Description page of Project Settings.


#include "ToonTankGameMode.h"
#include "ToonTank/Pawns/PawnTank.h"
#include "ToonTank/Pawns/PawnTurret.h"
#include "ToonTank/Pawns/PawnTurretUp.h"
#include "ToonTank/PlayerController/PlayerControllerBase.h"
#include "Kismet/GameplayStatics.h"

void AToonTankGameMode::BeginPlay() 
{
    Super::BeginPlay();

    HandleGameStart();
}

void AToonTankGameMode::ActorDied(AActor* DeadActor) 
{
    if(DeadActor == PlayerTank)
    {
        PlayerTank->HandleDestruction();
        HandleGameOver(false, GameScore);

        if(PlayerControllerRef)
        {
            PlayerControllerRef->SetPlayerEnabledState(false);
        }
    }
    else if(APawnTurret* DestroyedTurret = Cast<APawnTurret>(DeadActor))
    {
        DestroyedTurret->HandleDestruction();
        --TargetTurrets;
        ++GameScore;
        if(TargetTurrets == 0)
        {
            HandleGameOver(true, GameScore);
        }
    }
    else if(APawnTurretUp* DestroyedTurretUp = Cast<APawnTurretUp>(DeadActor))
    {
        DestroyedTurretUp->HandleDestruction();
        --TargetTurrets;
        ++GameScore;
        if(TargetTurrets == 0)
        {
            HandleGameOver(true,GameScore);
        }
    }
}

void AToonTankGameMode::HandleGameStart() 
{
    TargetTurrets = GetTargetTurretsCount() + GetTargetTurretsUpCount();
    PlayerTank = Cast<APawnTank>(UGameplayStatics::GetPlayerPawn(this, 0));
    PlayerControllerRef = Cast<APlayerControllerBase>(UGameplayStatics::GetPlayerController(this, 0));
    
    GameStart();

    if(PlayerControllerRef)
    {
        PlayerControllerRef->SetPlayerEnabledState(false);
        
        FTimerHandle PlayerEnabledHandle;
        FTimerDelegate PlayerEnabledDelegate = FTimerDelegate::CreateUObject(PlayerControllerRef, 
        &APlayerControllerBase::SetPlayerEnabledState, true);

        GetWorld()->GetTimerManager().SetTimer(PlayerEnabledHandle, PlayerEnabledDelegate, StartDelay, false);
    }
}

void AToonTankGameMode::HandleGameOver(bool PlayerWon, int32 Score) 
{
    GameOver(PlayerWon, Score);
}

int32 AToonTankGameMode::GetTargetTurretsCount() 
{
    TArray<AActor*> TurretActors;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), APawnTurret::StaticClass(), TurretActors);

    return TurretActors.Num();
}

int32 AToonTankGameMode::GetTargetTurretsUpCount() 
{
    TArray<AActor*> TurretUpActors;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), APawnTurretUp::StaticClass(), TurretUpActors);

    return TurretUpActors.Num();
}
