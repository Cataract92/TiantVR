// Fill out your copyright notice in the Description page of Project Settings.

#include "VRGestureRegComponent.h"

// Sets default values for this component's properties
UVRGestureRegComponent::UVRGestureRegComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UVRGestureRegComponent::BeginPlay()
{
	Super::BeginPlay();

	TArray<UActorComponent*> MotionControllerArray = GetWorld()->GetFirstPlayerController()->GetPawn()->GetComponentsByClass(UMotionControllerComponent::StaticClass());

	if (MotionControllerArray.Num() == 0) return;

	for (UActorComponent* ControllerActor : MotionControllerArray) {
		UMotionControllerComponent* Controller = Cast<UMotionControllerComponent>(ControllerActor);
		if (Controller->Hand == EControllerHand::Right) {
			UPlayerInput* Input = GetWorld()->GetFirstPlayerController()->PlayerInput;
		}
	}
}


// Called every frame
void UVRGestureRegComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UVRGestureRegComponent::RightMotionControllerTriggerPressed()
{
	UE_LOG(LogTemp, Warning, TEXT("Trigger Pressed"));
}

