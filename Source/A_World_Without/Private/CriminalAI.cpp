// Fill out your copyright notice in the Description page of Project Settings.


#include "CriminalAI.h"
#include "GameFramework/CharacterMovementComponent.h"

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