// Fill out your copyright notice in the Description page of Project Settings.

#include "ChooseNextWaypoint.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"

#include "PatrollingGuard.h" // TODO remove coupling

EBTNodeResult::Type UChooseNextWaypoint::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory)
{

	// TODO Protect against empty patrol route
	
	auto BlackboardComp = OwnerComp.GetBlackboardComponent();

	auto AIController = OwnerComp.GetAIOwner();
	auto Pawn = Cast<APatrollingGuard>(AIController->GetPawn());
	auto PatrolPoints = Pawn->PatrolPointsCPP;

	auto Index = BlackboardComp->GetValueAsInt(IndexKey.SelectedKeyName);
	auto PatrolPoint = PatrolPoints[Index];
	BlackboardComp->SetValueAsObject(WaypointKey.SelectedKeyName, PatrolPoint);

	Index = (Index + 1) % PatrolPoints.Num();
	BlackboardComp->SetValueAsInt(IndexKey.SelectedKeyName, Index);

	return EBTNodeResult::Succeeded;
}
