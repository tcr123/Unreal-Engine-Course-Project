// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ShooterCharacter.generated.h"

class AGun;

UCLASS()
class SIMPLESHOOTER_API AShooterCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AShooterCharacter();

	UFUNCTION(BlueprintPure)
	bool IsDead() const;

	UFUNCTION(BlueprintPure)
	float BloodPercent() const;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void Shoot();

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const & DamageEvent, class AController * EventInstigator, AActor * DamageCauser) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	//Movement
	void PlayerMoveForward(float AxisValue);
	void PlayerMoveRight(float AxisValue);
	//View
	void PlayerLookUp(float AxisValue);
	void PlayerLookRight(float AxisValue);
	void PlayerLookUpRate(float AxisValue);
	void PlayerLookRightRate(float AxisValue);

	//Action
	void PlayerJump();

	//Variable
	UPROPERTY(EditAnywhere)
	float RotationRate = 40.f;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AGun> GunClass;

	UPROPERTY(EditDefaultsOnly)
	float MaxHealth = 100.f;

	UPROPERTY(VisibleAnywhere)
	float Health;

	UPROPERTY()
	AGun* Gun;
};
