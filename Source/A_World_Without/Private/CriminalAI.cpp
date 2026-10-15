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