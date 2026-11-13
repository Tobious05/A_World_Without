// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_FindPatrolWaypoint.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "Kismet/GameplayStatics.h"
#include "Waypoint.h"

EBTNodeResult::Type UBTTask_FindPatrolWaypoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	//gets all the waypoints in the level
	TArray<AActor*> FoundWaypoints;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AWaypoint::StaticClass(), FoundWaypoints);

	if (FoundWaypoints.Num() > 0)
	{
		//picks a random waypoint
		int32 RandomIndex = FMath::RandRange(0, FoundWaypoints.Num() - 1);
		AActor* TargetWaypoint = FoundWaypoints[RandomIndex];

		//saves the waypoint to blackboard key named "TargetWaypoint"
		OwnerComp.GetBlackboardComponent()->SetValueAsObject(FName("TargetWaypoint"), TargetWaypoint);

		return EBTNodeResult::Succeeded;
	}
	return EBTNodeResult::Failed;
}

