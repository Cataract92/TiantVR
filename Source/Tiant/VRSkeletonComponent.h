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
	
	UPROPERTY(EditAnywhere)
	float MaxHeight = 160.f;

	UPROPERTY(EditAnywhere)
	float AngleNeck = 40;
	
	UPROPERTY(EditAnywhere)
	float AngleChest = 40;

	UPROPERTY(EditAnywhere)
	bool bUseCustomRations = false;

	UPROPERTY(EditAnywhere, meta = (EditCondition = bUseCustomRations))
	float RatioEyesToHead = (1. - 0.936);
	UPROPERTY(EditAnywhere, meta = (EditCondition = bUseCustomRations))
	float RatioHeadToNeck = (1 - 0.870);
	UPROPERTY(EditAnywhere, meta = (EditCondition = bUseCustomRations))
	float RatioNeckToChest = (0.870 - 0.720);
	UPROPERTY(EditAnywhere, meta = (EditCondition = bUseCustomRations))
	float RatioChestToHip = (0.720 - 0.530);

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	FVector GetEyesPosition() const;
	FVector GetHeadPosition() const;
	FVector GetNeckPosition() const;
	FVector GetChestPosition() const;
	FVector GetHipPosition() const;

private:

	FVector Eyes = FVector(), Head = FVector(), Neck = FVector(), Chest = FVector(), Hip = FVector();
	FVector EyesToHead = FVector(), HeadToNeck = FVector(), NeckToChest = FVector(), ChestToHip = FVector();

};
