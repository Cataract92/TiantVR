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

	AVRTriggerVolume();

	virtual void Tick(float DeltaTime) override;
	
private:

	bool IsOverlappingCamera(float DeltaTime, UCameraComponent* Camera);

	bool IsBeetweenPoints(float MinX, float MidX, float MaxX) const;
};
