// Fill out your copyright notice in the Description page of Project Settings.


#include "PedestrianAI.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Waypoint.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"

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

	MoveToWaypoint();
	
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
	TArray<AActor*> FoundWaypoints;		//creates array to hold all the waypoints in the level
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AWaypoint::StaticClass(), FoundWaypoints);

	if (FoundWaypoints.Num() > 0)		//check if one was found
	{
		int32 RandomIndex = FMath::RandRange(0, FoundWaypoints.Num() - 1);	//pick random way point
		AActor* TargetWaypoint = FoundWaypoints[RandomIndex];

		UAIBlueprintHelperLibrary::SimpleMoveToActor(GetController(), TargetWaypoint);	//makes AI walk to it using NavMesh
	}
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

	MoveToWaypoint();		//recall this function to fix a bug where pedestrians stand still after being stopped by traffic lights

}

void APedestrianAI::ReactToLRAD()
{
	WalkSpeed = 600.0f;		//sets the walk speed to sprint

	if (GetCharacterMovement())
	{
		GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
	}

	MoveToWaypoint();	//makes AI pick a new waypoint to flee to
}