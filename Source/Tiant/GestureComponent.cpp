// Fill out your copyright notice in the Description page of Project Settings.

#include "GestureComponent.h"
#include "GlobalDatabaseActor.h"


// Sets default values for this component's properties
UGestureComponent::UGestureComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGestureComponent::BeginPlay()
{
	Super::BeginPlay();
	// ...

}


// Called every frame
void UGestureComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	//AGlobalDatabaseActor::GetInstance()->PrintDebugMessage(GetAttachParent()->GetRelativeTransform().GetLocation().ToString());
	// ...
}

void UGestureComponent::StartGestureRecording()
{
	AGlobalDatabaseActor::GetInstance()->PrintDebugMessage("Start");

	StartRecordingGesture(RecordingInverval, "", DrawLine, LineMesh, LineMaterial, LineOffset, FRotator(0.f,-GetOwner()->GetActorRotation().Yaw,0.f));
}

void UGestureComponent::StopGestureRecording(bool SaveToDB)
{
	if (SaveToDB){
		KnownGesturesDB = AGlobalDatabaseActor::GetInstance()->GetGestureRecognitionActor()->GetGestureDatabase();
		StopRecordingGesture(SaveToDB);
		AGlobalDatabaseActor::GetInstance()->PrintDebugMessage("Gesture Saved");
	}
	else
	{
		FVRGesture Gesture = StopRecordingGesture(SaveToDB);
		AGlobalDatabaseActor::GetInstance()->PrintDebugMessage(FindGesture());
	}
	
	
}

