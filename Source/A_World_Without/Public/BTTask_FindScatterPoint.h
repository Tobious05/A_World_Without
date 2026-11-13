// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlueprintBase.h"
#include "BTTask_FindScatterPoint.generated.h"

/**
 * 
 */
UCLASS()
class A_WORLD_WITHOUT_API UBTTask_FindScatterPoint : public UBTTask_BlueprintBase
{
	GENERATED_BODY()
	
public:

	//function that automatically runs when the behavior tree reaches this node and reports back if it succeeded or failed
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

};
