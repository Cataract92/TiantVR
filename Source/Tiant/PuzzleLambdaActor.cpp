// Fill out your copyright notice in the Description page of Project Settings.

#include "PuzzleLambdaActor.h"
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

	
	AddLambdaDefinition(ELambdaEnum::LE_Scene1_OrderTiantMove, [this](AActor* TriggeringActor, AActor* TriggeredActor, FTriggerableParams& Params) {
		
		UCameraComponent* Camera = GetWorld()->GetFirstPlayerController()->GetPawn()->FindComponentByClass<UCameraComponent>();

		if (Camera)
		{
			FMinimalViewInfo ViewInfo;
			Camera->GetCameraView(GetWorld()->GetDeltaSeconds(), OUT ViewInfo);

			FHitResult HitResult;
			GetWorld()->LineTraceSingleByObjectType(OUT HitResult, ViewInfo.Location, ViewInfo.Location + ViewInfo.Rotation.Vector() * 10000, FCollisionObjectQueryParams());
			FVector HitLocation = HitResult.Location;

			ATiantCharacter* TiantCharacter = AGlobalDatabaseActor::GetInstance()->GetTiant();
			AAIController* Controller = Cast<AAIController>(TiantCharacter->GetController());

			EPathFollowingRequestResult::Type Result = Controller->MoveToLocation(HitLocation);
		}
	});

	AddLambdaDefinition(ELambdaEnum::LE_Scene1_OrderTiantUse, [this](AActor* TriggeringActor, AActor* TriggeredActor, FTriggerableParams& Params)
	{
		UCameraComponent* Camera = GetWorld()->GetFirstPlayerController()->GetPawn()->FindComponentByClass<UCameraComponent>();

		if (Camera)
		{
			FMinimalViewInfo ViewInfo;
			Camera->GetCameraView(GetWorld()->GetDeltaSeconds(), OUT ViewInfo);

			FHitResult HitResult;
			GetWorld()->LineTraceSingleByObjectType(OUT HitResult, ViewInfo.Location, ViewInfo.Location + ViewInfo.Rotation.Vector() * 10000, FCollisionObjectQueryParams());

			if (!HitResult.GetActor() || !HitResult.GetActor()->FindComponentByClass<UTriggerableComponent>())
				return;

			AGlobalDatabaseActor::GetInstance()->GetTiant()->OrderUse(HitResult.GetActor());
		}
	});
	

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
			Params.Actors[0]->SetActorHiddenInGame(false);
			Cast<UTriggerableComponent>(Params.Actors[0]->GetComponentByClass(UTriggerableComponent::StaticClass()))->Enable(true);
		} , 8.f, false);
	});

	/*
	 * TriggeredActor: Sphere
	 * Actors[0]: Wall to Move
	 * Vectors[0]: Movedirection
	 */
	AddLambdaDefinition(ELambdaEnum::LE_Scene1_MoveWall, [this](AActor* TriggeringActor, AActor* TriggeredActor, FTriggerableParams& Params)
	{
		// Disable this Trigger, so it just happens once.
		Cast<UTriggerableComponent>(TriggeredActor->GetComponentByClass(UTriggerableComponent::StaticClass()))->Enable(false);

		Params.Actors[0]->SetActorLocation(Params.Actors[0]->GetActorLocation() + Params.Vectors[0]);

		TArray<UActorComponent*> Components = AGlobalDatabaseActor::GetInstance()->GetTiant()->GetComponentsByClass(UTriggerableComponent::StaticClass());

		for(auto var : Components)
		{
			UTriggerableComponent* Component = Cast<UTriggerableComponent>(var);

			if (Component->GetPredefinedParameters().Strings.Contains("use"))
				Component->Enable(true);
		}
	});

	/*
	 * TriggeringActor: Tiant
	 * TriggeredActor: Sphere
	 * Actors[0]: Wall to Move
	 * Vectors[0]: Movedirection
	 */
	AddLambdaDefinition(ELambdaEnum::LE_Scene1_MoveWall2, [this](AActor* TriggeringActor, AActor* TriggeredActor, FTriggerableParams& Params)
	{
		// Disable this Trigger, so it just happens once.
		Cast<UTriggerableComponent>(TriggeredActor->GetComponentByClass(UTriggerableComponent::StaticClass()))->Enable(false);

		Params.Actors[0]->SetActorLocation(Params.Actors[0]->GetActorLocation() + Params.Vectors[0]);

		TArray<UActorComponent*> Components = AGlobalDatabaseActor::GetInstance()->GetTiant()->GetComponentsByClass(UTriggerableComponent::StaticClass());

		for (auto var : Components)
		{
			UTriggerableComponent* Component = Cast<UTriggerableComponent>(var);

			if (Component->GetPredefinedParameters().Strings.Contains("there"))
				Component->Enable(true);
		}
	});

	/*
	* TriggeringActor: Tiant
	* TriggeredActor: Mirror
	* Vectors[0]: Rotation as Vector
	*/
	AddLambdaDefinition(ELambdaEnum::LE_Scene1_RotateMirror, [this](AActor* TriggeringActor, AActor* TriggeredActor, FTriggerableParams& Params)
	{
		// Disable this Trigger, so it just happens once.
		Cast<UTriggerableComponent>(TriggeredActor->GetComponentByClass(UTriggerableComponent::StaticClass()))->Enable(false);

		TriggeredActor->SetActorRotation(TriggeredActor->GetActorRotation() + FRotator(Params.Vectors[0].X, Params.Vectors[0].Y, Params.Vectors[0].Z));
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

	if (!ActionMap.Contains(Params.TriggerAction)) return;

	for (TArray<UTriggerableComponent*>::TConstIterator IterComponent(ActionMap[Params.TriggerAction]); IterComponent; ++IterComponent)
	{
		if ((*IterComponent)->GetTriggeringAction() != Params.TriggerAction || !(*IterComponent)->IsEnabled() || (*IterComponent)->GetTriggeringActor() != TriggeringActor || (Params.TriggeredActor!= nullptr && Params.TriggeredActor != (*IterComponent)->GetOwner())) 
			continue;

		if ((*IterComponent)->GetTriggeringAction() == ETriggerActionEnum::TAE_OnPhraseRecognition && !(*IterComponent)->GetPredefinedParameters().Strings[0].Equals(Params.Strings[0]))
			continue;

		if ((*IterComponent)->GetTriggeringAction() == ETriggerActionEnum::TAE_OnGesture && (!(*IterComponent)->GetPredefinedParameters().Strings[0].Equals(Params.Strings[0]) || !(*IterComponent)->GetPredefinedParameters().Strings[1].Equals(Params.Strings[1])))
			continue;

		FTriggerableParams::SetParameter(Params, (*IterComponent)->GetPredefinedParameters());
		LambdasMap[(*IterComponent)->GetLambdaEnum()](TriggeringActor, (*IterComponent)->GetOwner(), Params);
	}

}

void APuzzleLambdaActor::RegisterLambda(UTriggerableComponent * TriggerableComponent, ETriggerActionEnum TriggerAction)
{
	if (!ActionMap.Contains(TriggerAction))
		ActionMap.Add(TriggerAction, TArray<UTriggerableComponent*>());

	if (!ActionMap[TriggerAction].Contains(TriggerableComponent))
		ActionMap[TriggerAction].Add(TriggerableComponent);
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



