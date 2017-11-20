// Fill out your copyright notice in the Description page of Project Settings.

#define OUT 

#include "TiantInteractionTask.h"
#include "Navigation/PathFollowingComponent.h"
#include "AIController.h"

EBTNodeResult::Type UTiantInteractionTask::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	bNotifyTick = true;
	bNotifyTaskFinished = true;

	AAIController* Controller = Cast<AAIController>(AGlobalDatabaseActor::GetInstance()->GetTiant()->GetController());

	UObject* Object = OwnerComp.GetBlackboardComponent()->GetValueAsObject("Target");
	if (!Object)
	{
		AGlobalDatabaseActor::GetInstance()->PrintDebugMessage("Object null");
		return EBTNodeResult::Failed;
	}

	AActor* Actor = Cast<AActor>(Object);

	if (!Actor)
	{
		AGlobalDatabaseActor::GetInstance()->PrintDebugMessage("Cast null");
		return EBTNodeResult::Failed;
	}

	FVector Location = Actor->GetActorLocation();

	EPathFollowingRequestResult::Type Result = Controller->MoveToLocation(Location);

	Cast<AActor>(OwnerComp.GetBlackboardComponent()->GetValueAsObject("Target"))->FindComponentByClass<UStaticMeshComponent>()->GetLocalBounds(OUT BoundMin, OUT BoundMax);

	if (Result == EPathFollowingRequestResult::Type::Failed)
		return EBTNodeResult::Failed;
	else
		return EBTNodeResult::InProgress;

}

void UTiantInteractionTask::OnTaskFinished(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTNodeResult::Type TaskResult)
{
	Super::OnTaskFinished(OwnerComp, NodeMemory, TaskResult);

	AAIController* Controller = Cast<AAIController>(AGlobalDatabaseActor::GetInstance()->GetTiant()->GetController());

	Controller->StopMovement();

	
	APuzzleLambdaActor* PuzzleLambdaActor = APuzzleLambdaActor::GetInstance();
	FTriggerableParams Params(ETriggerActionEnum::TAE_OnTiantInteraction);

	Params.TriggeredActor = Cast<AActor>(OwnerComp.GetBlackboardComponent()->GetValueAsObject("Target"));

	OwnerComp.GetBlackboardComponent()->ClearValue("Target");

	PuzzleLambdaActor->FireLambda(AGlobalDatabaseActor::GetInstance()->GetTiant(), Params);
}

void UTiantInteractionTask::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	FVector TiantLocation = AGlobalDatabaseActor::GetInstance()->GetTiant()->GetActorLocation();
	FVector TargetLocation = Cast<AActor>(OwnerComp.GetBlackboardComponent()->GetValueAsObject("Target"))->GetActorLocation();

	if (FVector::Dist2D(TiantLocation,TargetLocation) <= (BoundMax - BoundMin).Size()+Distance)
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
}

