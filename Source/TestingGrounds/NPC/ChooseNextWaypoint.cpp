// Fill out your copyright notice in the Description page of Project Settings.

#include "ChooseNextWaypoint.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"

#include "PatrolRoute.h"

EBTNodeResult::Type UChooseNextWaypoint::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory)
{
	
	auto BlackboardComp = OwnerComp.GetBlackboardComponent();

	auto ControlledPawn = OwnerComp.GetAIOwner()->GetPawn();
	auto PatrolRoute = ControlledPawn->FindComponentByClass<UPatrolRoute>();
	if (!ensure(PatrolRoute)) return EBTNodeResult::Failed;

	auto PatrolPoints = PatrolRoute->GetPatrolPoints();

	if (PatrolPoints.Num() == 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("A guard is missing patrol points"))
		return EBTNodeResult::Failed;
	}

	auto Index = BlackboardComp->GetValueAsInt(IndexKey.SelectedKeyName);
	auto PatrolPoint = PatrolPoints[Index];
	BlackboardComp->SetValueAsObject(WaypointKey.SelectedKeyName, PatrolPoint);

	Index = (Index + 1) % PatrolPoints.Num();
	BlackboardComp->SetValueAsInt(IndexKey.SelectedKeyName, Index);

	return EBTNodeResult::Succeeded;
}
