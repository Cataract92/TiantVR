// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CameraViewRayCaster.h"
#include "Engine.h"
#include "Camera/CameraComponent.h"
#include "Tiant/ViewRayCastHitable.h"

#define OUT
#define DEBUG ()

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
		if (AActor* HitActor = GetValidActorByHitResult(HitResult)) {
			HitActor->SetActorLocation(HitActor->GetActorLocation() + FVector(0.f, 0.f, 1.f));
		}
	}
}

uint16 UCameraViewRayCaster::GetMaxReflections() const {
	return MaxReflections;
}

AActor* UCameraViewRayCaster::GetValidActorByHitResult(FHitResult& HitResult, uint16 ReflectionDepth) const
{
	// If an Actor is found && found Actor has RayCastHitable-Component && Distance <= Component-Distance
	if (HitResult.GetActor() && HitResult.GetActor()->FindComponentByClass<UViewRayCastHitable>() && HitResult.GetActor()->FindComponentByClass<UViewRayCastHitable>()->GetHitRange() >= HitResult.Distance) {
			if (HitResult.GetActor()->FindComponentByClass<UViewRayCastHitable>()->DoReflect()) {
				if (ReflectionDepth >= GetMaxReflections()) {
					return nullptr;
				}

				FVector TraceVector = HitResult.TraceEnd - HitResult.TraceStart;
				TraceVector.Normalize();

				FVector NewTraceVector = TraceVector - 2 * FVector::DotProduct(TraceVector, HitResult.ImpactNormal) *  HitResult.ImpactNormal;

				FHitResult NewHitResult;
				GetWorld()->LineTraceSingleByObjectType(OUT NewHitResult, HitResult.Location, HitResult.Location + NewTraceVector * RayCastRange, FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody));

				//DrawDebugLine(GetWorld(), HitResult.Location, HitResult.Location + NewTraceVector * RayCastRange, FColor(100.f, 0.f, 0.f), false, 0.f, 0, 0.5f);

				return GetValidActorByHitResult(NewHitResult, ReflectionDepth + 1);

			}	else 
				return HitResult.GetActor();
	}
	else
		return nullptr;
}

