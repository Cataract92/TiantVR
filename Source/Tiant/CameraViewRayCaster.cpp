// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CameraViewRayCaster.h"
#include "Engine.h"
#include "Camera/CameraComponent.h"
#include "Tiant/ViewRayCastHitable.h"

#define OUT

// Sets default values for this component's properties
UCameraViewRayCaster::UCameraViewRayCaster()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UCameraViewRayCaster::BeginPlay()
{
	Super::BeginPlay();

	PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
	
	UE_LOG(LogTemp, Warning, TEXT("Location %s"),*PlayerPawn->GetActorLocation().ToString());
}


// Called every frame
void UCameraViewRayCaster::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	UCameraComponent* Camera = PlayerPawn->FindComponentByClass<UCameraComponent>();

	if (Camera) {
		FMinimalViewInfo ViewInfo;
		Camera->GetCameraView(DeltaTime, OUT ViewInfo);
		DrawDebugLine(GetWorld(), ViewInfo.Location + ViewInfo.Rotation.Vector() * 100.f, ViewInfo.Location + ViewInfo.Rotation.Vector() * RayCastRange, FColor(0.f, 0.f, 100.f), false, 0.f, 0, 1.f);
		
		FHitResult HitResult;
		GetWorld()->LineTraceSingleByObjectType(OUT HitResult, ViewInfo.Location, ViewInfo.Location + ViewInfo.Rotation.Vector() * RayCastRange, FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody));
		if (HitResult.GetActor()) {
			if (HitResult.GetActor()->FindComponentByClass<UViewRayCastHitable>())
				HitResult.GetActor()->SetActorLocation(HitResult.GetActor()->GetActorLocation() + FVector(0.f, 0.f, 1.f));
		}
	}
	// ...
}

