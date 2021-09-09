// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterAIController.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "ShooterCharacter.h"

void AShooterAIController::BeginPlay() 
{
    Super::BeginPlay();

    APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
    
    if(AIBehaviour!=nullptr)
    {
        RunBehaviorTree(AIBehaviour);

        GetBlackboardComponent()->SetValueAsVector(TEXT("PlayerLocation"), PlayerPawn->GetActorLocation());
        GetBlackboardComponent()->SetValueAsVector(TEXT("StartLocation"), GetPawn()->GetActorLocation());
    }
}

void AShooterAIController::Tick(float DeltaTime) 
{
    Super::Tick(DeltaTime);

}

bool AShooterAIController::isDead() const
{
    AShooterCharacter* AIShooter = Cast<AShooterCharacter>(GetPawn());
    if(AIShooter!=nullptr)
    {
        return AIShooter->IsDead();
    }

    return true;
}
