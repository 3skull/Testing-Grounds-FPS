// Fill out your copyright notice in the Description page of Project Settings.
#include "ChooseNextWayPoint.h"
#include "AIController.h"
#include "PatrollingGuard.h" //TODO Remove later

EBTNodeResult::Type UChooseNextWayPoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) {

	auto AIController = OwnerComp.GetAIOwner();
	auto ControlledPawn = AIController->GetPawn();
	auto PatrollingGuard = Cast<APatrollingGuard>(ControlledPawn);
	auto PatrolPoints = PatrollingGuard->PatrolPointsCPP;


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
