// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PedestrianAI.h"
#include "CriminalAI.generated.h"

/**
 * 
 */
UCLASS()
class A_WORLD_WITHOUT_API ACriminalAI : public APedestrianAI
{
	GENERATED_BODY()

protected:

	virtual void BeginPlay() override;

	//timer for handling the isolation timer
	FTimerHandle IsolationCheckTimerHandle;

	//tracks how long the criminal has been isolated
	float CurrentIsolationTime = 0.0f;

	//will run every 0.2s to check if pedestrians are within the radius of criminal
	void CheckIsolation();

	//will spawn the laser and remove the criminal
	void EliminateCriminal();



public:

	ACriminalAI();

	virtual void ReactToLRAD() override;

	virtual void HaltMovement() override;

	//the radius of how far the criminals must be from pedestrians to be classed as "isolated"
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Elimination")
	float IsolationRadius = 400.0f;

	//how long the criminal must remain isolated before elimination
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Elimination")
	float RequiredIsolationTime = 1.5f;

	//spawn the laser actor when eliminated
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Elimination")
	TSubclassOf<AActor> LaserBeamClass;
	
};
