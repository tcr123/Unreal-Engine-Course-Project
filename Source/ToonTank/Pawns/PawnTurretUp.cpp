// Fill out your copyright notice in the Description page of Project Settings.


#include "PawnTurretUp.h"
#include "PawnTank.h"
#include "Kismet/GameplayStatics.h"

// Called when the game starts or when spawned
void APawnTurretUp::BeginPlay()
{
	Super::BeginPlay();
	
    GetWorld()->GetTimerManager().SetTimer(FireRateTimerHandle, this, &APawnTurretUp::CheckFireCondition, FireRate, true);

    PlayerPawn = Cast<APawnTank>(UGameplayStatics::GetPlayerPawn(this, 0));
}

void APawnTurretUp::HandleDestruction() 
{
    Super::HandleDestruction();
    Destroy();
}

// Called every frame
void APawnTurretUp::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    if(!PlayerPawn || ReturnDistanceToPlayer() > FireRange)
    {
        return;
    }

    RotateTurret(PlayerPawn->GetActorLocation());
}

void APawnTurretUp::CheckFireCondition() 
{
    if(!PlayerPawn)
    {
        return;
    }

    if(ReturnDistanceToPlayer() <= FireRange && PlayerPawn->GetIsPlayerAlive())
    {
        Fire();
    }
}

float APawnTurretUp::ReturnDistanceToPlayer() 
{
    if(!PlayerPawn)
    {
        return 0.f;
    }
    
    return FVector::Dist(PlayerPawn->GetActorLocation(), GetActorLocation());
}
