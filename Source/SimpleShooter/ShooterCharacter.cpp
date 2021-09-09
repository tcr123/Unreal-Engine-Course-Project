// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterCharacter.h"
#include "Gun.h"
#include "Components/CapsuleComponent.h"
#include "SimpleShooterGameModeBase.h"

// Sets default values
AShooterCharacter::AShooterCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AShooterCharacter::BeginPlay()
{
	Super::BeginPlay();
	Health =  MaxHealth;
	
	Gun = GetWorld()->SpawnActor<AGun>(GunClass);
	GetMesh()->HideBoneByName(TEXT("weapon_r"), EPhysBodyOp::PBO_None);
	Gun->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("weapon_socket"));
	Gun->SetOwner(this);
}

// Called every frame
void AShooterCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AShooterCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//Axis
	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &AShooterCharacter::PlayerMoveForward);
	PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &AShooterCharacter::PlayerMoveRight);
	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &AShooterCharacter::PlayerLookUp);
	PlayerInputComponent->BindAxis(TEXT("LookRight"), this, &AShooterCharacter::PlayerLookRight);
	PlayerInputComponent->BindAxis(TEXT("LookUpRate"), this, &AShooterCharacter::PlayerLookUpRate);
	PlayerInputComponent->BindAxis(TEXT("LookRightRate"), this, &AShooterCharacter::PlayerLookRightRate);

	//Action
	PlayerInputComponent->BindAction(TEXT("Jump"), IE_Pressed, this, &AShooterCharacter::PlayerJump);
	PlayerInputComponent->BindAction(TEXT("Shoot"), IE_Pressed, this, &AShooterCharacter::Shoot);
}

float AShooterCharacter::TakeDamage(float DamageAmount, struct FDamageEvent const & DamageEvent, class AController * EventInstigator, AActor * DamageCauser) 
{
	float DamageToApply = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	DamageToApply = FMath::Min(Health, DamageToApply);
	Health -= DamageToApply;
	UE_LOG(LogTemp, Warning, TEXT("Health: %f"), Health);

	if(IsDead())
	{
		ASimpleShooterGameModeBase* GameModeBase = GetWorld()->GetAuthGameMode<ASimpleShooterGameModeBase>();
		if(GameModeBase != nullptr)
		{
			GameModeBase->PawnKilled(this);
		}

		DetachFromControllerPendingDestroy();
		GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}

	return DamageToApply;
}

bool AShooterCharacter::IsDead() const
{
	return Health <= 0;
}

float AShooterCharacter::BloodPercent() const
{
	return Health / MaxHealth;
}

void AShooterCharacter::PlayerMoveForward(float AxisValue) 
{
	AddMovementInput(GetActorForwardVector() * AxisValue);
}

void AShooterCharacter::PlayerMoveRight(float AxisValue) 
{
	AddMovementInput(GetActorRightVector() * AxisValue);
}

void AShooterCharacter::PlayerLookUp(float AxisValue) 
{
	AddControllerPitchInput(AxisValue);
}

void AShooterCharacter::PlayerLookRight(float AxisValue) 
{
	AddControllerYawInput(AxisValue);
}

void AShooterCharacter::PlayerLookUpRate(float AxisValue) 
{
	AddControllerPitchInput(AxisValue * RotationRate * GetWorld()->GetDeltaSeconds());
}

void AShooterCharacter::PlayerLookRightRate(float AxisValue) 
{
	AddControllerYawInput(AxisValue * RotationRate * GetWorld()->GetDeltaSeconds());
}

void AShooterCharacter::PlayerJump() 
{
	Jump();
}

void AShooterCharacter::Shoot() 
{
	Gun->PullTrigger();
}


