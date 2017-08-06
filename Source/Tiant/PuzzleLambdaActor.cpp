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

	AddLambdaDefinition(ELambdaEnum::LE_Scene1_RotateMirror, [](AActor* TriggeringActor, AActor* TriggeredActor, FTriggerableParams& Params) {
		
		if (Params.Vectors.Num() == 0)
		{
			AGlobalDatabaseActor::GetInstance()->PrintDebugMessage("Num == 0");
			return;
		}
		AGlobalDatabaseActor::GetInstance()->PrintDebugMessage("Rotate!");
		TriggeredActor->SetActorRotation(Params.Vectors[0].Rotation());
		
	});

	AddLambdaDefinition(ELambdaEnum::LE_Scene1_DoNothing, [](AActor* TriggeringActor, AActor* TriggeredActor, FTriggerableParams& Params)
	{
		AGlobalDatabaseActor::GetInstance()->PrintDebugMessage("Nothing!");
	});

}

// Called every frame
void APuzzleLambdaActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APuzzleLambdaActor::AddLambdaDefinition(ELambdaEnum LambdaEnum, TFunction<void(AActor* TriggeringActor, AActor* TriggeredActor, FTriggerableParams& Params)> Lamda)
{
	LambdasMap.Add(LambdaEnum, Lamda);
}

TFunction<void(AActor* TriggeringActor, AActor* TriggeredActor, FTriggerableParams& Params)> APuzzleLambdaActor::GetLambda(ELambdaEnum LambdaEnum)
{
	return LambdasMap[LambdaEnum];
}

void APuzzleLambdaActor::FireLambda(AActor* TriggeringActor, ETriggerActionEnum TriggerAction, FTriggerableParams& Params)
{

	if (!TriggeringActorMap.Contains(TriggeringActor)) return;
	if (!TriggeringActorMap[TriggeringActor].Contains(TriggerAction)) return;

	TArray<AActor*> TriggeredActors = TriggeringActorMap[TriggeringActor][TriggerAction];
	
	for (TArray<AActor*>::TConstIterator IterActor(TriggeredActors); IterActor; ++IterActor) {
		TArray<UActorComponent*> Components = (*IterActor)->GetComponentsByClass(UTriggerableComponent::StaticClass());

		for (TArray<UActorComponent*>::TConstIterator IterComp(Components); IterComp; ++IterComp) {
			UTriggerableComponent* Component = static_cast<UTriggerableComponent*>(*IterComp);
			
			if (Component->GetTriggeringAction() != TriggerAction) continue;

			FTriggerableParams::SetParameter(Params, Component->GetPredefinedParameters());

			GetLambda(Component->GetLambdaEnum())(TriggeringActor, *IterActor, Params);
		}
	}
}

void APuzzleLambdaActor::RegisterLambda(AActor * TriggeringActor, AActor * TriggeredActor, ETriggerActionEnum TriggerAction)
{
	if (!TriggeringActorMap.Contains(TriggeringActor)) {
		TriggeringActorMap.Add(TriggeringActor, TMap<ETriggerActionEnum, TArray<AActor*>>());
	}
	if (!TriggeringActorMap[TriggeringActor].Contains(TriggerAction)) {
		TriggeringActorMap[TriggeringActor].Add(TriggerAction, TArray<AActor*>());
	}
	TriggeringActorMap[TriggeringActor][TriggerAction].Add(TriggeredActor);
}

APuzzleLambdaActor* APuzzleLambdaActor::GetInstance()
{
	// Prevents Nullptrexception in Iterator if this is called before or while Gameinitializaion
	if (!GEngine->GameViewport->GetWorld()) return nullptr;

	// Iterate through all GlobalDatabaseActors and return the first one found
	// (only one should exist)
	for (TActorIterator<APuzzleLambdaActor> ActorItr(GEngine->GameViewport->GetWorld()); ActorItr; ++ActorItr) {
		return *ActorItr;
	}

	// If no GDActor is found return null
	return nullptr;
}



