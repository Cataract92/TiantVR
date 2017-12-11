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

	UPROPERTY(EditAnywhere)
	float RecordingInverval = 0.5f;

	UPROPERTY(EditAnywhere)
	bool DrawLine = true;
	
	UPROPERTY(EditAnywhere, meta = (EditCondition = DrawLine))
	UStaticMesh* LineMesh = nullptr;

	UPROPERTY(EditAnywhere, meta = (EditCondition = DrawLine))
	UMaterial* LineMaterial = nullptr;

	UPROPERTY(EditAnywhere, meta = (EditCondition = DrawLine))
	FVector LineOffset = FVector(0, 0, 0);
	
	UPROPERTY(EditAnywhere, meta = (EditCondition = DrawLine))
	FRotator RotationOffset = FRotator(0, 0, 0);

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void StartGestureRecording();

	void StopGestureRecording(bool SaveToDB);
};
