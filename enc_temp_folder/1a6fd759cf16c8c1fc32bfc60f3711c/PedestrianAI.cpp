// Fill out your copyright notice in the Description page of Project Settings.


#include "PedestrianAI.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
APedestrianAI::APedestrianAI()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//setting default values
	CurrentState = EPedestrianState::Idle;
	WalkSpeed = 150.0f;

	//apply the walk speed to the Unreal Engine movement comp
	if (GetCharacterMovement())
	{
		GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
	}

}

// Called when the game starts or when spawned
void APedestrianAI::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APedestrianAI::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APedestrianAI::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

//Handles logic for AI moving to a target
void APedestrianAI::MoveToWaypoint()
{
	//the navigation logic will be added later
	//currently blank to clear compiling errors
}

//Handles logic for AI running from a dangerous noise of object
void APedestrianAI::Flee(FVector ThreatLocation)
{
	//will add math for calculating evasion paths later
	//currently blank to clear compiling errors
}

void APedestrianAI::HaltMovement()
{
	CurrentState = EPedestrianState::Idle;

	if (GetCharacterMovement())
	{
		GetCharacterMovement()->MaxWalkSpeed = 0.0f;	//sets the walk speed to 0 when the AI should stop moving
	}
}

void APedestrianAI::ResumeMovement()
{
	CurrentState = EPedestrianState::Walking;

	if (GetCharacterMovement())
	{
		GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;	//sets the walkspeed back to the original walk speed when they should go back to moving
	}
}