// Fill out your copyright notice in the Description page of Project Settings.
#include "ChooseNextWayPoint.h"
#include "AIController.h"

#include "PatrolRoute.h"

EBTNodeResult::Type UChooseNextWayPoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) {




	// Get Patrol Points
	auto AIController = OwnerComp.GetAIOwner();
	auto ControlledPawn = AIController->GetPawn();
	auto PatrolRoute = ControlledPawn->FindComponentByClass<UPatrolRoute>();

	if (!ensure(PatrolRoute)) {
		return EBTNodeResult::Failed;
	}


	
	auto PatrolPoints = PatrolRoute->GetPatrolPoints();

	if (PatrolPoints.Num() == 0) {
		UE_LOG(LogTemp, Warning, TEXT("No Patrol Points"));
		return EBTNodeResult::Failed;
	}


	// Set next waypoint
	UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();
	auto Index = BlackboardComp->GetValueAsInt(IndexKey.SelectedKeyName);
	BlackboardComp->SetValueAsObject(WayPoint.SelectedKeyName, PatrolPoints[Index]);

	//cycle index
	auto NextIndex = (Index + 1) % PatrolPoints.Num();
	BlackboardComp->SetValueAsInt(IndexKey.SelectedKeyName, NextIndex);

	UE_LOG(LogTemp, Warning, TEXT("Waypoint index: %i"), Index);
	return EBTNodeResult::Succeeded;
}
