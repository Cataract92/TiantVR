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

	GesturesDatabase = NewObject<URunebergVR_Gestures_Database>();
	
	GetWorld()->GetFirstPlayerController()->GetPawn()->InputComponent->BindAction("RightTrigger", IE_Pressed, this, &AGestureRecognitionActor::PressedRightTrigger);
	GetWorld()->GetFirstPlayerController()->GetPawn()->InputComponent->BindAction("RightTrigger", IE_Released, this, &AGestureRecognitionActor::ReleasedRightTrigger);
	
	GetWorld()->GetFirstPlayerController()->GetPawn()->InputComponent->BindAction("LeftTrigger", IE_Pressed, this, &AGestureRecognitionActor::PressedLeftTrigger);
	GetWorld()->GetFirstPlayerController()->GetPawn()->InputComponent->BindAction("LeftTrigger", IE_Released, this, &AGestureRecognitionActor::ReleasedLeftTrigger);

	GetWorld()->GetFirstPlayerController()->GetPawn()->InputComponent->BindAction("RightGrip", IE_Pressed, this, &AGestureRecognitionActor::PressedRightGrip);
	GetWorld()->GetFirstPlayerController()->GetPawn()->InputComponent->BindAction("RightGrip", IE_Released, this, &AGestureRecognitionActor::ReleasedRightGrip);

	GetWorld()->GetFirstPlayerController()->GetPawn()->InputComponent->BindAction("LeftGrip", IE_Pressed, this, &AGestureRecognitionActor::PressedLeftGrip);
	GetWorld()->GetFirstPlayerController()->GetPawn()->InputComponent->BindAction("LeftGrip", IE_Released, this, &AGestureRecognitionActor::ReleasedLeftGrip);

}

// Called every frame
void AGestureRecognitionActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

URunebergVR_Gestures_Database* AGestureRecognitionActor::GetGestureDatabase() const
{
	return GesturesDatabase;
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
	GetRightHand()->StopGestureRecording(false);
}

void AGestureRecognitionActor::PressedLeftTrigger()
{
	GetLeftHand()->StartGestureRecording();
}

void AGestureRecognitionActor::ReleasedLeftTrigger()
{
	GetLeftHand()->StopGestureRecording(false);
}

void AGestureRecognitionActor::PressedRightGrip()
{
	GetRightHand()->StartGestureRecording();
}

void AGestureRecognitionActor::ReleasedRightGrip()
{
	GetRightHand()->StopGestureRecording(true);
}

void AGestureRecognitionActor::PressedLeftGrip()
{
	GetLeftHand()->StartGestureRecording();
}

void AGestureRecognitionActor::ReleasedLeftGrip()
{
	GetLeftHand()->StopGestureRecording(true);
}



