// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerVolume.h"
#include "Camera/CameraComponent.h"
#include "VRTriggerVolume.generated.h"

/**
 * 
 */
UCLASS()
class TIANT_API AVRTriggerVolume : public ATriggerVolume
{
	GENERATED_BODY()
	
public:

	bool IsOverlapping(float DeltaTime, const FVector& Position) const;
	
private:

	
	static bool IsBeetweenPoints(float MinX, float MidX, float MaxX);
};
