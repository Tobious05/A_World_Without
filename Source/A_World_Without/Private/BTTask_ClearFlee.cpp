// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_ClearFlee.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

EBTNodeResult::Type UBTTask_ClearFlee::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{

	//gets rid of the IsFleeing task from memory and lets it return of patrolling
	OwnerComp.GetBlackboardComponent()->ClearValue(FName("IsFleeing"));

	//get the AI controller and the character its controlling
	AAIController* AICon = OwnerComp.GetAIOwner();
	if (AICon && AICon->GetPawn())
	{
		ACharacter* AICharacter = Cast<ACharacter>(AICon->GetPawn());
		if (AICharacter)
		{
			//resets walkspeed back to normal patrolling speed
			AICharacter->GetCharacterMovement()->MaxWalkSpeed = 150.0f;
		}
	}
	return EBTNodeResult::Succeeded;
}