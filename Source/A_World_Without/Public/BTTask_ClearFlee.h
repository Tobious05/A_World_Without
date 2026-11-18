// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlueprintBase.h"
#include "BTTask_ClearFlee.generated.h"

/**
 * 
 */
UCLASS()
class A_WORLD_WITHOUT_API UBTTask_ClearFlee : public UBTTask_BlueprintBase
{
	GENERATED_BODY()
	

public:
	//task for the fleeing to be aborted so AI can return to patrolling
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

};
