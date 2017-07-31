// Fill out your copyright notice in the Description page of Project Settings.

#include "VRTriggerVolume.h"
#include "TriggerComponent.h"
#include "GlobalDatabaseActor.h"
#include "Camera/CameraComponent.h"

#define OUT

AVRTriggerVolume::AVRTriggerVolume()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bTickEvenWhenPaused = true;
	UE_LOG(LogTemp, Warning, TEXT("Construct"));

}

void AVRTriggerVolume::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AGlobalDatabaseActor::GetInstance()->PrintDebugMessage("Tick");

	UE_LOG(LogTemp, Warning, TEXT("Tick"));

	IsOverlappingCamera(DeltaTime, GetWorld()->GetFirstPlayerController()->GetPawn()->FindComponentByClass<UCameraComponent>());
}

bool AVRTriggerVolume::IsOverlappingCamera(float DeltaTime, UCameraComponent* Camera) {
	if (!Camera) return false;

	FMinimalViewInfo ViewInfo;
	Camera->GetCameraView(DeltaTime, OUT ViewInfo);

	FVector CameraLocation = ViewInfo.Location;
	FVector Min = GetComponentsBoundingBox().Min;
	FVector Max = GetComponentsBoundingBox().Max;

	if (IsBeetweenPoints(Min.X, CameraLocation.X, Max.X) && IsBeetweenPoints(Min.Y, CameraLocation.Y, Max.Y) && IsBeetweenPoints(Min.Z, CameraLocation.Z, Max.Z)) {
		UTriggerComponent* Component = (UTriggerComponent*) GetParentActor()->GetComponentByClass(UTriggerComponent::StaticClass());
		
		FTriggerableParams Params;
		Params.bUseRotation = true;

		Component->FireLambda(ETriggerActionEnum::TAE_CameraOverlap, Params);

		AGlobalDatabaseActor::GetInstance()->PrintDebugMessage("Fire Camera1");

		return true;
	}
	
	return false;
}

bool AVRTriggerVolume::IsBeetweenPoints(float MinX, float MidX, float MaxX) const {
	return ( (MinX < MidX && MidX < MaxX) || (MinX > MidX && MidX > MaxX));
}

