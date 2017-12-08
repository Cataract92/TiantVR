// Fill out your copyright notice in the Description page of Project Settings.

#include "VRTriggerVolume.h"
#include "TriggerComponent.h"
#include "GlobalDatabaseActor.h"
#include "Camera/CameraComponent.h"

#define OUT

bool AVRTriggerVolume::IsOverlapping(float DeltaTime, const FVector& Position) const
{
	FVector Min = GetComponentsBoundingBox().Min;
	FVector Max = GetComponentsBoundingBox().Max;

	return IsBeetweenPoints(Min.X, Position.X, Max.X) && IsBeetweenPoints(Min.Y, Position.Y, Max.Y) && IsBeetweenPoints(Min.Z, Position.Z, Max.Z);
}

bool AVRTriggerVolume::IsBeetweenPoints(float MinX, float MidX, float MaxX)
{
	return  MinX < MidX && MidX < MaxX || MinX > MidX && MidX > MaxX;
}

