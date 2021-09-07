// Fill out your copyright notice in the Description page of Project Settings.

#include "Door.h"
#include "Components/AudioComponent.h"
#include "GameFramework/Actor.h"
#include "Components/PrimitiveComponent.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"

// Sets default values for this component's properties
UDoor::UDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	// ...
}


// Called when the game starts
void UDoor::BeginPlay()
{
	Super::BeginPlay();
	// ...
	InitialYaw = GetOwner()->GetActorRotation().Yaw;
	CurrentYaw = InitialYaw;
	OpenAngle += InitialYaw;

	FindPressurePlate();
	FindAudioComponent();
}


// Called every frame
void UDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (TotalMassOfActor() > MassToOpenDoor)
	{
		OpenDoor(DeltaTime);
		DoorLastOpened = GetWorld()->GetTimeSeconds();
	}
	else
	{
		if(GetWorld()->GetTimeSeconds() - DoorLastOpened > DoorClosedDelay)
		{
			CloseDoor(DeltaTime);
		}
	}
}

void UDoor::OpenDoor(float DeltaTime)
{
	// UE_LOG(LogTemp, Display, TEXT("%s"), *GetOwner()->GetActorRotation().ToString());
	// UE_LOG(LogTemp, Display, TEXT("Yaw is : %f"), GetOwner()->GetActorRotation().Yaw);

	CurrentYaw = FMath::FInterpTo(CurrentYaw, OpenAngle, DeltaTime, DoorOpenSpeed);

	FRotator OpenDoor = GetOwner()->GetActorRotation();
	OpenDoor.Yaw = CurrentYaw;
	GetOwner()->SetActorRotation(OpenDoor);

	if(!AudioComponent){return;}

	CloseDoorSound = false;
	if(!OpenDoorSound)
	{
		AudioComponent->Play();
		OpenDoorSound = true;
	}
}

void UDoor::CloseDoor(float DeltaTime)
{
	CurrentYaw = FMath::FInterpTo(CurrentYaw, InitialYaw, DeltaTime, DoorCloseSpeed);

	FRotator CloseDoor = GetOwner()->GetActorRotation();
	CloseDoor.Yaw = CurrentYaw;
	GetOwner()->SetActorRotation(CloseDoor);

	if(!AudioComponent){return;}
	
	OpenDoorSound = false;
	if(!CloseDoorSound)
	{
		AudioComponent->Play();
		CloseDoorSound = true;
	}
}

float UDoor::TotalMassOfActor() const
{
	float SumOfMass = 0.f;

	TArray<AActor*> OverlappingActor;
	if(!PressurePlate)
	{
		return SumOfMass;
	}
	PressurePlate->GetOverlappingActors(OverlappingActor);

	for(AActor* Actor: OverlappingActor)
	{
		UPrimitiveComponent* MassToAdd = Actor->FindComponentByClass<UPrimitiveComponent>();
		SumOfMass += MassToAdd->GetMass();
	}
	
	return SumOfMass;
}

void UDoor::FindAudioComponent()
{
	AudioComponent = GetOwner()->FindComponentByClass<UAudioComponent>();
	if(!AudioComponent)
	{
		UE_LOG(LogTemp, Error, TEXT("%s, audio component missing"), *GetOwner()->GetName());
	}
}

void UDoor::FindPressurePlate()
{
	if(!PressurePlate)
	{
		UE_LOG(LogTemp, Error, TEXT("Actor: %s"), *GetOwner()->GetName());
		UE_LOG(LogTemp, Error, TEXT("has DoorComponent but no PressurePlate"));
	}
}