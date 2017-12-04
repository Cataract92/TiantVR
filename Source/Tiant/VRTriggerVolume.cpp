// Fill out your copyright notice in the Description page of Project Settings.

#include "VRTriggerVolume.h"
#include "TriggerComponent.h"
#include "GlobalDatabaseActor.h"
#include "Camera/CameraComponent.h"

#define OUT

bool AVRTriggerVolume::IsOverlapping(float DeltaTime, const FVector& Position) const
{
	FVector CameraLocation = Position;
	FVector Min = GetComponentsBoundingBox().Min;
	FVector Max = GetComponentsBoundingBox().Max;

	return IsBeetweenPoints(Min.X, CameraLocation.X, Max.X) && IsBeetweenPoints(Min.Y, CameraLocation.Y, Max.Y) && IsBeetweenPoints(Min.Z, CameraLocation.Z, Max.Z);
}

bool AVRTriggerVolume::IsBeetweenPoints(float MinX, float MidX, float MaxX)
{
	return  MinX < MidX && MidX < MaxX || MinX > MidX && MidX > MaxX;
}

