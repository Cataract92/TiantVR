// Fill out your copyright notice in the Description page of Project Settings.

#include "TiantCharacter.h"
#include "AIController.h"
#include "Engine/Engine.h"
#include <BehaviorTree/BehaviorTree.h>
#include <BehaviorTree/BlackboardComponent.h>
#include "GlobalDatabaseActor.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Object.h"


// Sets default values
ATiantCharacter::ATiantCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//BehaviorTree->BlackboardAsset = NewObject<UBlackboardData>();
	//BehaviorTree->BlackboardAsset->UpdatePersistentKey<UBlackboardKeyType_Object>(FName("Target"));

	BlackboardComponent = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackboardComponent"));
	BehaviorTreeComponent = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorTreeComponent"));
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

void ATiantCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	BehaviorTree->BlackboardAsset = NewObject<UBlackboardData>();
	BehaviorTree->BlackboardAsset->UpdatePersistentKey<UBlackboardKeyType_Object>(FName("Target"));

	BlackboardComponent->InitializeBlackboard(*BehaviorTree->BlackboardAsset);
}

void ATiantCharacter::OrderUse(AActor* Target)
{
	AAIController* Controller = Cast<AAIController>(this->GetController());

	BlackboardComponent->SetValueAsObject("Target", Target);
	BehaviorTreeComponent->StartTree(*BehaviorTree);
}
