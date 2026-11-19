// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractableDevice.h"
#include "TimerManager.h"

// Sets default values
AInteractableDevice::AInteractableDevice()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bIsActive = false;			//Sets the devices to not active
	bIsOnCooldown = false;		//starts the cooldown at false
	CooldownDuration = 3.0f;	//Sets cooldown duration to 3s

}

// Called when the game starts or when spawned
void AInteractableDevice::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AInteractableDevice::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AInteractableDevice::TriggerDevice_Implementation()
{
	//Logic overriden in child blueprints
}

//function for starting the cooldown timer so devices cant be spammed
void AInteractableDevice::StartCooldown()
{
	if (CooldownDuration <= 0.0f)
	{
		return;
	}

	bIsOnCooldown = true;	//stops the device being clicked
	GetWorldTimerManager().SetTimer(CooldownTimerHandle, this, &AInteractableDevice::ResetCooldown, CooldownDuration, false);	//Starts the cooldown and calls ResetCooldown once finished
}

void AInteractableDevice::ResetCooldown()
{
	bIsOnCooldown = false;		//allow the device to be clicked again
}

//returns seconds left on cooldown
float AInteractableDevice::GetRemainingCooldown() const
{
	if (!bIsOnCooldown)
	{
		return 0.0f;		//return 0 if the device isnt on cooldown
	}

	return FMath::Max(0.0f, GetWorldTimerManager().GetTimerRemaining(CooldownTimerHandle));		//returns how much time is left (no negative numbers)
}