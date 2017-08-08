// Fill out your copyright notice in the Description page of Project Settings.

#include "TriggerComponent.h"
#include "VRTriggerVolume.h"

#define OUT
// Sets default values for this component's properties
UTriggerComponent::UTriggerComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UTriggerComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

// Called every frame
void UTriggerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	//OnTick
	FireOnTickEvent(DeltaTime);

	//CameraOverlappingEvent
	FireOnCameraOverlappingEvent(DeltaTime);

}

void UTriggerComponent::FireLambda(FTriggerableParams& Params )
{
	APuzzleLambdaActor::GetInstance()->FireLambda(GetOwner(), Params);
}

void UTriggerComponent::FireOnTickEvent(float DeltaTime)
{
	FTriggerableParams OnTickParams(ETriggerActionEnum::TAE_OnTick);
	OnTickParams.DeltaTime = DeltaTime;
	FireLambda(OnTickParams);
}

bool bIsCameraOverlapping = false;

void UTriggerComponent::FireOnCameraOverlappingEvent(float DeltaTime)
{
	TArray<AActor*> AttachedActors;
	GetOwner()->GetAttachedActors(OUT AttachedActors);

	bool bIsCameraOverlappingCheck = false;

	for (TArray<AActor*>::TConstIterator ActorItr(AttachedActors); ActorItr; ++ActorItr)
	{
		if ((*ActorItr)->IsA(AVRTriggerVolume::StaticClass()))
		{
			UCameraComponent* Cam = static_cast<UCameraComponent*>(GetWorld()->GetFirstPlayerController()->GetPawn()->FindComponentByClass<UCameraComponent>());

			bIsCameraOverlappingCheck = static_cast<AVRTriggerVolume*>(*ActorItr)->IsOverlappingCamera(DeltaTime, Cam);
			break;
		}
	}

	// If Camera is Overlapping now, but wasn't before fire CameraStartOverlap-Event
	if (bIsCameraOverlappingCheck && !bIsCameraOverlapping)
	{
		bIsCameraOverlapping = true;

		FTriggerableParams CameraOverlappParams(ETriggerActionEnum::TAE_CameraStartOverlap);
		FireLambda(CameraOverlappParams);
	}


	// If Camera isn't Overlapping now, but was before fire CameraStopOverlap-Event
	if (!bIsCameraOverlappingCheck && bIsCameraOverlapping)
	{
		bIsCameraOverlapping = false;

		FTriggerableParams CameraOverlappParams(ETriggerActionEnum::TAE_CameraStopOverlap);
		FireLambda(CameraOverlappParams);
	}
}