// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "VRSkeletonComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TIANT_API UVRSkeletonComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UVRSkeletonComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:

	FVector Eyes = FVector(), Head = FVector(), Neck = FVector(), Chest = FVector(), Hip = FVector();
	FVector EyesToHead = FVector(), HeadToNeck = FVector(), NeckToChest = FVector(), ChestToHip = FVector();

	float RatioEyesToHead = (1. - 0.936);
	float RatioHeadToNeck = (1 - 0.870);
	float RatioNeckToChest = (0.870 - 0.720);
	float RatioChestToHip = (0.720 - 0.530);

	UPROPERTY(EditAnywhere)
	FRotator Rotator;

};
