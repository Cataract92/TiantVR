// Fill out your copyright notice in the Description page of Project Settings.

#include "TiantInteractionTask.h"
#include "Developer/AITestSuite/Classes/Actions/TestPawnAction_Log.h"
#include "Navigation/PathFollowingComponent.h"
#include "AIController.h"

EBTNodeResult::Type UTiantInteractionTask::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* Controller = Cast<AAIController>(AGlobalDatabaseActor::GetInstance()->GetTiant()->GetController());

	EPathFollowingRequestResult::Type Result = Controller->MoveToLocation(Cast<AActor>(OwnerComp.GetBlackboardComponent()->GetValueAsObject("Target"))->GetActorLocation());

	if (Result == EPathFollowingRequestResult::Type::Failed)
		return EBTNodeResult::Failed;
	else
		return EBTNodeResult::InProgress;

	
}

void UTiantInteractionTask::OnTaskFinished(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTNodeResult::Type TaskResult)
{
	APuzzleLambdaActor* PuzzleLambdaActor = APuzzleLambdaActor::GetInstance();
	FTriggerableParams Params(ETriggerActionEnum::TAE_OnTiantInteraction);
	AActor* Target = Cast<AActor>(OwnerComp.GetBlackboardComponent()->GetValueAsObject("Target"));
	PuzzleLambdaActor->FireLambda(AGlobalDatabaseActor::GetTiant(), Params);
}

void UTiantInteractionTask::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	FVector TiantLocation = AGlobalDatabaseActor::GetInstance()->GetTiant()->GetActorLocation();
	FVector TargetLocation = Cast<AActor>(OwnerComp.GetBlackboardComponent()->GetValueAsObject("Target"))->GetActorLocation();

	if (FVector::Dist2D(TiantLocation,TargetLocation) <= Distance)
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
}

