// Fill out your copyright notice in the Description page of Project Settings.

#include "ChooseNextWaypoint.h"

EBTNodeResult::Type UChooseNextWaypoint::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory)
{
	UE_LOG(LogTemp, Warning, TEXT("MUCCA: AI from C++ is running"))
	return EBTNodeResult::Succeeded;
}
