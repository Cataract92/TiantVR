// Fill out your copyright notice in the Description page of Project Settings.

#include "PuzzleLambdaActor.h"
#include "TriggerableComponent.h"


// Sets default values
APuzzleLambdaActor::APuzzleLambdaActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APuzzleLambdaActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APuzzleLambdaActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APuzzleLambdaActor::AddLambdaDefinition(ELambdaEnum LambdaEnum, TFunction<void(AActor* TriggeringActor, FTriggerableParams& Params)> Lamda)
{
	LambdasMap.Add(LambdaEnum, Lamda);
}

TFunction<void(AActor* TriggeringActor, FTriggerableParams& Params)> APuzzleLambdaActor::GetLambda(ELambdaEnum LambdaEnum)
{
	return LambdasMap[LambdaEnum];
}

void APuzzleLambdaActor::FireLambda(AActor* TriggeringActor, ETriggerActionEnum TriggerAction, FTriggerableParams& Params)
{
	TArray<AActor*> TriggeredActors = TriggeringActorMap[TriggeringActor][TriggerAction];
	
	for (TArray<AActor*>::TConstIterator IterActor(TriggeredActors); IterActor; ++IterActor) {
		TArray<UActorComponent*> Components = (*IterActor)->GetComponentsByClass(UTriggerableComponent::StaticClass());

		for (TArray<UActorComponent*>::TConstIterator IterComp(Components); IterComp; ++IterComp) {
			UTriggerableComponent* Component = (UTriggerableComponent*) *IterComp;
			if (Component->GetTriggeringAction() != TriggerAction) return;
			GetLambda(Component->GetLambdaEnum())(TriggeringActor, Params);
		}

	}
}

void APuzzleLambdaActor::RegisterLambda(AActor * TriggeringActor, AActor * TriggeredActor, ETriggerActionEnum TriggerAction)
{
	
}

