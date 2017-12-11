// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GestureComponent.h"
#include "GestureRecognitionActor.generated.h"

UCLASS()
class TIANT_API AGestureRecognitionActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGestureRecognitionActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	URunebergVR_Gestures_Database* GetGestureDatabase() const;

	UGestureComponent* GetRightHand();

	UGestureComponent* GetLeftHand();

private:
	
	URunebergVR_Gestures_Database* GesturesDatabase;

	void PressedRightTrigger();
	void ReleasedRightTrigger();
	void PressedLeftTrigger();
	void ReleasedLeftTrigger();

	void PressedRightGrip();
	void ReleasedRightGrip();
	void PressedLeftGrip();
	void ReleasedLeftGrip();
};
