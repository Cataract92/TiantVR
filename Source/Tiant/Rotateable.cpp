// Fill out your copyright notice in the Description page of Project Settings.

#include "Rotateable.h"


// Sets default values for this component's properties
URotateable::URotateable()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void URotateable::BeginPlay()
{
	Super::BeginPlay();

	TriggeringActor = GetWorld()->GetFirstPlayerController()->GetPawn();
	Camera = TriggeringActor->FindComponentByClass<UCameraComponent>();
	InitalRotator = GetOwner()->GetActorRotation();
	// ...
	
}


// Called every frame
void URotateable::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (TriggerPlate->IsOverlappingCamera(DeltaTime, Camera)) {
		if (bAddVector) {
			GetOwner()->SetActorRotation(GetOwner()->GetActorRotation() + RotationVector);
		}
		else {
			GetOwner()->SetActorRotation(RotationVector);
		}
	}
	else {
		GetOwner()->SetActorRotation(InitalRotator);
		FMinimalViewInfo ViewInfo;
		Camera->GetCameraView(DeltaTime, OUT ViewInfo);
		//TextRenderer->GetTextRender()->SetText(FText::FromString(FString::Printf(TEXT("Location: %s"), &ViewInfo.Location)));
	}
}
