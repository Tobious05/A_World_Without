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

public:

	ACriminalAI();

	virtual void ReactToLRAD() override;

	virtual void HaltMovement() override;
	
};
