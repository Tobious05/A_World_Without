// Fill out your copyright notice in the Description page of Project Settings.


#include "CriminalAI.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "TimerManager.h"
#include "EngineUtils.h"

void ACriminalAI::BeginPlay()
{
	Super::BeginPlay();

	//used a timer instead of on tick to save CPU since doing it on tick for over 50 pedestrians would be straining
	//this is a looping timer that runs every 0.2s to CheckIsolation()
	GetWorldTimerManager().SetTimer(IsolationCheckTimerHandle, this, &ACriminalAI::CheckIsolation, 0.2f, true);
}

ACriminalAI::ACriminalAI()		//Criminals starting data
{
	WalkSpeed = 300.0f;		//criminals walk faster than normal pedestrians

	if (GetCharacterMovement())		//apply criminal walk speed to the movement comp of unreal
	{
		GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
	}
}

void ACriminalAI::ReactToLRAD()
{
	//overrides parent function and does nothing
	//empty so the criminal does nothing and keeps moving normally
}

void ACriminalAI::HaltMovement()
{
	//empty so the criminal does nothing when the halt movement function is called
}

//check to see if pedestrian is within the isolatio radius of criminal
void ACriminalAI::CheckIsolation()
{
	bool bIsPedestrianNearby = false;	//starts off as false

	for (TActorIterator<APedestrianAI> It(GetWorld()); It; ++It)	//loops through all pedestrians in the level
	{
		APedestrianAI* Ped = *It;

		if (!Ped || Ped == this || Ped->IsA(ACriminalAI::StaticClass()))	//skip if its invalid or another criminal
		{
			continue;
		}

		//measures the distance between criminal and pedestrian
		float Distance = FVector::Dist(GetActorLocation(), Ped->GetActorLocation());

		//if pedestrian is within the radius then set to true for bIsPedestrianNearby
		if (Distance <= IsolationRadius)
		{
			bIsPedestrianNearby = true;
			break;
		}
	}

	if (bIsPedestrianNearby)
	{
		CurrentIsolationTime = 0.0f;	//if a pedestrian is nearby then put count back to zero
	}
	else
	{
		CurrentIsolationTime += 0.2f;		//if no one is nearby then add 0.2s

		if (CurrentIsolationTime >= RequiredIsolationTime)
		{
			EliminateCriminal();		//if the criminal has been isolated for long enough then eliminate them
		}
	}
}

//spawns the laser beam and destroys the criminal
void ACriminalAI::EliminateCriminal()
{
	GetWorldTimerManager().ClearTimer(IsolationCheckTimerHandle);		//Stop the timer so it doesnt rerun while criminal actor is being destroyed

	if (LaserBeamClass)
	{
		GetWorld()->SpawnActor<AActor>(LaserBeamClass, GetActorLocation(), FRotator::ZeroRotator);	//spawn laser at criminals location
	}

	Destroy();		//Remove the criminal
}