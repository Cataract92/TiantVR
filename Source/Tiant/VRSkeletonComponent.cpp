// Fill out your copyright notice in the Description page of Project Settings.

#include "VRSkeletonComponent.h"
#include "Camera/CameraComponent.h"
#include "GlobalDatabaseActor.h"
#include <string>


// Sets default values for this component's properties
UVRSkeletonComponent::UVRSkeletonComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UVRSkeletonComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UVRSkeletonComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	FMinimalViewInfo ViewInfo;
	GetOwner()->FindComponentByClass<UCameraComponent>()->GetCameraView(DeltaTime,ViewInfo);
	
	Eyes.Set(ViewInfo.Location.X, ViewInfo.Location.Y + 100, ViewInfo.Location.Z);
	
	Head = ViewInfo.Rotation.RotateVector(FVector(0, 0, Eyes.Z) * RatioEyesToHead) + Eyes ;

	FVector tmp = Eyes - Head;
	tmp.Normalize(1.f);
	Neck = Head + (tmp * MaxHeight * RatioHeadToNeck);

	tmp = FVector(0, 0, -1) * MaxHeight * RatioNeckToChest;

	FVector EyesToNeckNormalized = Eyes - Neck;
	EyesToNeckNormalized.Normalize();

	if (bUseThresholds)
	{

		float angle = FMath::RadiansToDegrees(FMath::Acos(FVector::DotProduct(EyesToNeckNormalized, FVector::UpVector)));

		if (angle > AngleNeck)
		{
			if (FVector::CrossProduct(EyesToNeckNormalized, FVector::UpVector).Y < 0)
			{
				angle *= -1;
			}

			if (angle > AngleNeck)
				tmp = tmp.RotateAngleAxis(-(angle - AngleNeck), ViewInfo.Rotation.Vector());
			else
				tmp = tmp.RotateAngleAxis(-(angle + AngleNeck), ViewInfo.Rotation.Vector());

		}

		Chest = Neck + tmp;

		tmp = FVector(0, 0, -1) * MaxHeight * RatioChestToHip;

		FVector NeckToChestNormalized = Neck - Chest;
		NeckToChestNormalized.Normalize();

		angle = FMath::RadiansToDegrees(FMath::Acos(FVector::DotProduct(NeckToChestNormalized, FVector::UpVector)));

		if (angle > AngleChest)
		{
			if (FVector::CrossProduct(NeckToChestNormalized, FVector::UpVector).Y < 0)
			{
				angle *= -1;
			}

			if (angle > AngleChest)
				tmp = tmp.RotateAngleAxis(-(angle - AngleChest), ViewInfo.Rotation.Vector());
			else
				tmp = tmp.RotateAngleAxis(-(angle + AngleChest), ViewInfo.Rotation.Vector());

		}

		Hip = Chest + tmp;

	} else {
		
		float angle = FMath::RadiansToDegrees(FMath::Acos(FVector::DotProduct(EyesToNeckNormalized, FVector::UpVector)));

		if (FVector::CrossProduct(EyesToNeckNormalized, FVector::UpVector).Y < 0)
		{
			angle *= -1;
		}

		tmp = tmp.RotateAngleAxis(-angle * AnglePercentNeck, ViewInfo.Rotation.Vector());

		Chest = Neck + tmp;

		tmp = FVector(0, 0, -1) * MaxHeight * RatioChestToHip;

		FVector NeckToChestNormalized = Neck - Chest;
		NeckToChestNormalized.Normalize();

		angle = FMath::RadiansToDegrees(FMath::Acos(FVector::DotProduct(NeckToChestNormalized, FVector::UpVector)));

		if (FVector::CrossProduct(NeckToChestNormalized, FVector::UpVector).Y < 0)
		{
			angle *= -1;
		}

		tmp = tmp.RotateAngleAxis(-angle * AnglePercentChest, ViewInfo.Rotation.Vector());
			
		Hip = Chest + tmp;

	}

	/*
	AGlobalDatabaseActor::GetInstance()->DevActors[0]->SetActorLocation(Eyes);
	AGlobalDatabaseActor::GetInstance()->DevActors[1]->SetActorLocation(Head);
	AGlobalDatabaseActor::GetInstance()->DevActors[2]->SetActorLocation(Neck);
	AGlobalDatabaseActor::GetInstance()->DevActors[3]->SetActorLocation(Chest);
	AGlobalDatabaseActor::GetInstance()->DevActors[4]->SetActorLocation(Hip);
	*/
	// ...
}

FVector UVRSkeletonComponent::GetEyesPosition() const
{
	return Eyes;
}

FVector UVRSkeletonComponent::GetHeadPosition() const
{
	return Head;
}

FVector UVRSkeletonComponent::GetNeckPosition() const
{
	return Neck;
}

FVector UVRSkeletonComponent::GetChestPosition() const
{
	return Chest;
}

FVector UVRSkeletonComponent::GetHipPosition() const
{
	return Hip;
}