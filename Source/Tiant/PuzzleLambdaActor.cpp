// Fill out your copyright notice in the Description page of Project Settings.

#include "PuzzleLambdaActor.h"
#include "TriggerableComponent.h"
#include "AIController.h"
#include "MySpeechRecognitionActor.h"

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

	/*
	AddLambdaDefinition(ELambdaEnum::LE_Scene1_RotateMirror, [](AActor* TriggeringActor, AActor* TriggeredActor, FTriggerableParams& Params) {
		
		if (Params.Vectors.Num() == 0)
		{
			return;
		}
		TriggeredActor->SetActorRotation(FRotator(Params.Vectors[0].X, Params.Vectors[0].Y, Params.Vectors[0].Z));
	});
	*/

	/*
	 * TriggeredActor: The Wall which starts this event
	 * Actor[0]: The Sphere, which gets enabled to enable next puzzle
	 * Vector[0]: Location for Tiant-MoveOrder
	 */
	AddLambdaDefinition(ELambdaEnum::LE_Scene1_InitTiant, [this](AActor* TriggeringActor, AActor* TriggeredActor, FTriggerableParams& Params)
	{
		// Disable this Trigger, so it just happens once.
		Cast<UTriggerableComponent>(TriggeredActor->GetComponentByClass(UTriggerableComponent::StaticClass()))->Enable(false);
		

		ATiantCharacter* TiantCharacter = AGlobalDatabaseActor::GetInstance()->GetTiant();
		AAIController* Controller = Cast<AAIController>(TiantCharacter->GetController());

		EPathFollowingRequestResult::Type Result = Controller->MoveToLocation(Params.Vectors[0]);

		FTimerHandle TimerHandle;
		GetWorldTimerManager().SetTimer(OUT TimerHandle, [Params]()
		{
			Cast<UTriggerableComponent>(Params.Actors[0]->GetComponentByClass(UTriggerableComponent::StaticClass()))->Enable(true);
		} , 8.f, false);
		
		
	});

	/*
	 * TriggeringActor: Sphere
	 * TriggeredActor: Wall to Move
	 */
	AddLambdaDefinition(ELambdaEnum::LE_Scene1_MoveWall, [this](AActor* TriggeringActor, AActor* TriggeredActor, FTriggerableParams& Params)
	{
		// Disable this Trigger, so it just happens once.
		Cast<UTriggerableComponent>(TriggeredActor->GetComponentByClass(UTriggerableComponent::StaticClass()))->Enable(false);

		Params.Actors[0]->SetActorLocation(Params.Actors[0]->GetActorLocation() + Params.Vectors[0]);

		AMySpeechRecognitionActor::GetInstance()->EnablePhrase("there",true);
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

void APuzzleLambdaActor::FireLambda(AActor* TriggeringActor,FTriggerableParams& Params)
{

	if (Params.TriggerAction == ETriggerActionEnum::TAE_NotSet)
	{
		AGlobalDatabaseActor::GetInstance()->PrintDebugMessage("Trigger Action not set");
		return;
	}

	if (!TriggeringActorMap.Contains(TriggeringActor)) return;
	if (!TriggeringActorMap[TriggeringActor].Contains(Params.TriggerAction)) return;

	TArray<AActor*> TriggeredActors = TriggeringActorMap[TriggeringActor][Params.TriggerAction];
	
	for (TArray<AActor*>::TConstIterator IterActor(TriggeredActors); IterActor; ++IterActor) {
		TArray<UActorComponent*> Components = (*IterActor)->GetComponentsByClass(UTriggerableComponent::StaticClass());

		for (TArray<UActorComponent*>::TConstIterator IterComp(Components); IterComp; ++IterComp) {
			UTriggerableComponent* Component = static_cast<UTriggerableComponent*>(*IterComp);
			
			if (Component->GetTriggeringAction() != Params.TriggerAction || !Component->IsEnabled() || (Params.TriggeredActor != nullptr && Params.TriggeredActor != Component->GetPredefinedParameters().TriggeredActor)) continue;

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
	if (!TriggeringActorMap[TriggeringActor][TriggerAction].Contains(TriggeredActor))
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



