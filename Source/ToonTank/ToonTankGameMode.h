// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ToonTankGameMode.generated.h"

class APawnTank;
class APawnTurret;
class APlayerControllerBase;

UCLASS()
class TOONTANK_API AToonTankGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
private:
	APawnTank* PlayerTank;
	APlayerControllerBase* PlayerControllerRef;
	int32 TargetTurrets = 0;
	int32 GameScore = 0;

	void HandleGameStart();
	void HandleGameOver(bool PlayerWon, int32 Score);
	int32 GetTargetTurretsCount();
	int32 GetTargetTurretsUpCount();

public:

	void ActorDied(AActor* DeadActor);

protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "GameLoop")
	int32 StartDelay = 2;

	virtual void BeginPlay() override;
	UFUNCTION(BlueprintImplementableEvent)
	void GameStart();
	UFUNCTION(BlueprintImplementableEvent)
	void GameOver(bool PlayerWon, int32 Score);

};
