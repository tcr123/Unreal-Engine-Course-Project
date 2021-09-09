// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PawnBase.h"
#include "PawnTurretUp.generated.h"

class APawnTank;

UCLASS()
class TOONTANK_API APawnTurretUp : public APawnBase
{
	GENERATED_BODY()
	
private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat", meta = (AllowPrivateAccess  = "true"))
	float FireRate = 1.5f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat", meta = (AllowPrivateAccess  = "true"))
	float FireRange = 800.0f;

	FTimerHandle FireRateTimerHandle;
	APawnTank* PlayerPawn;

	void CheckFireCondition();

	float ReturnDistanceToPlayer();

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void HandleDestruction() override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
};
