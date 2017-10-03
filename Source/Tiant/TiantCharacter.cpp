// Fill out your copyright notice in the Description page of Project Settings.

#include "TiantCharacter.h"
#include "AIController.h"
#include "Engine/Engine.h"
#include "Runtime/ActorSequence/Private/ActorSequencePrivatePCH.h"
#include <BehaviorTree/BehaviorTree.h>
#include <BehaviorTree/BlackboardComponent.h>
#include "GlobalDatabaseActor.h"


// Sets default values
ATiantCharacter::ATiantCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BlackboardComponent = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BehaviorComponent"));
}

// Called when the game starts or when spawned
void ATiantCharacter::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ATiantCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ATiantCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ATiantCharacter::OrderUse(AActor* Target)
{
	AGlobalDatabaseActor::GetInstance()->PrintDebugMessage("UseOrder");

	AAIController* Controller = Cast<AAIController>(this->GetController());

	BlackboardComponent->InitializeBlackboard(*BehaviorTree->BlackboardAsset);
	AGlobalDatabaseActor::GetInstance()->PrintDebugMessage("InitBlackboard");
	BlackboardComponent->SetValueAsObject("Target", Target);
	AGlobalDatabaseActor::GetInstance()->PrintDebugMessage("Set Target");
	BlackboardComponent->SetValueAsVector("TargetVector", Target->GetActorLocation());
	AGlobalDatabaseActor::GetInstance()->PrintDebugMessage("SetTargetVector");

	Controller->RunBehaviorTree(BehaviorTree);
	AGlobalDatabaseActor::GetInstance()->PrintDebugMessage("RanBehavior");
}
