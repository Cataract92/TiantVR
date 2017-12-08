// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine.h"
#include "RunebergVR_Gestures.h"
#include "GestureComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TIANT_API UGestureComponent : public URunebergVR_Gestures
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGestureComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void StartGestureRecording();

	void StopGestureRecording();
};
