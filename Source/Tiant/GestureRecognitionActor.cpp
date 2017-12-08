// Fill out your copyright notice in the Description page of Project Settings.

#include "GestureRecognitionActor.h"


// Sets default values
AGestureRecognitionActor::AGestureRecognitionActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AGestureRecognitionActor::BeginPlay()
{
	Super::BeginPlay();
	
	GetWorld()->GetFirstPlayerController()->GetPawn()->InputComponent->BindAction("RightTrigger", IE_Pressed, this, &AGestureRecognitionActor::PressedRightTrigger);
	GetWorld()->GetFirstPlayerController()->GetPawn()->InputComponent->BindAction("LeftTrigger", IE_Pressed, this, &AGestureRecognitionActor::PressedLeftTrigger);
	GetWorld()->GetFirstPlayerController()->GetPawn()->InputComponent->BindAction("RightTrigger", IE_Released, this, &AGestureRecognitionActor::ReleasedRightTrigger);
	GetWorld()->GetFirstPlayerController()->GetPawn()->InputComponent->BindAction("LeftTrigger", IE_Released, this, &AGestureRecognitionActor::ReleasedLeftTrigger);
}

// Called every frame
void AGestureRecognitionActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

UGestureComponent* AGestureRecognitionActor::GetRightHand()
{
	TArray<UActorComponent*> Components = GetWorld()->GetFirstPlayerController()->GetPawn()->GetComponentsByClass(UGestureComponent::StaticClass());

	for (auto Component : Components)
	{
		if (Component->GetName().Equals("Gesture_R"))
			return Cast<UGestureComponent>(Component);
		
	}

	return nullptr;

}

UGestureComponent* AGestureRecognitionActor::GetLeftHand()
{
	TArray<UActorComponent*> Components = GetWorld()->GetFirstPlayerController()->GetPawn()->GetComponentsByClass(UGestureComponent::StaticClass());

	for (auto Component : Components)
	{
		if (Component->GetName().Equals("Gesture_L"))
			return Cast<UGestureComponent>(Component);

	}

	return nullptr;
}

void AGestureRecognitionActor::PressedRightTrigger()
{
	GetRightHand()->StartGestureRecording();
}

void AGestureRecognitionActor::ReleasedRightTrigger()
{
	GetRightHand()->StopGestureRecording();
}

void AGestureRecognitionActor::PressedLeftTrigger()
{
	GetLeftHand()->StartGestureRecording();
}

void AGestureRecognitionActor::ReleasedLeftTrigger()
{
	GetLeftHand()->StopGestureRecording();
}



