// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "PawnBase.generated.h"

class UCapsuleComponent;
class AProjectileBase;
class UHealthComponent;
class UMatineeCameraShake;

UCLASS()
class TOONTANK_API APawnBase : public APawn
{
	GENERATED_BODY()

private:
	//Component
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess  = "true"))
	UCapsuleComponent* CapsuleComp;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess  = "true"))
	UStaticMeshComponent* BashMesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess  = "true"))
	UStaticMeshComponent* TurretMesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	USceneComponent* ProjectileSpawnPoint;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Health", meta = (AllowPrivateAccess = "true"))
	UHealthComponent* HealthComponent;
	//ProjectileType
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ProjectileType", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<AProjectileBase> ProjectileClass;

	UPROPERTY(EditAnywhere, Category = "Effects")
	UParticleSystem* DealthParticle;
	//SoundEffect
	UPROPERTY(EditAnywhere, Category = "Effects")
	USoundBase* DealthSound;
	//CameraShake
	UPROPERTY(EditAnywhere, Category = "Effects")
	TSubclassOf<UMatineeCameraShake> DealthShake;

public:
	// Sets default values for this pawn's properties
	APawnBase();

	virtual void HandleDestruction();

protected:
	void RotateTurret(FVector LookAtTarget);

	void Fire();

};
