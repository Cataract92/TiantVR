// Fill out your copyright notice in the Description page of Project Settings.

#include "VRSkeletonComponent.h"
#include "Camera/CameraComponent.h"
#include "GlobalDatabaseActor.h"


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
	
	Eyes.Set(ViewInfo.Location.X - 100, ViewInfo.Location.Y, ViewInfo.Location.Z);
	
	Head = (Rotator + ViewInfo.Rotation).RotateVector(FVector(0, 0, Eyes.Z) * RatioEyesToHead) + Eyes ;

	FVector tmp = Head - Eyes;
	tmp.Normalize(1.f);
	Neck = Head + -(tmp * Head.Z * RatioHeadToNeck);

	tmp = Eyes - Neck;	
	tmp.Normalize(1.f);
	Chest = Neck + -(tmp * Head.Z * RatioNeckToChest);

	tmp = Neck - Chest;
	tmp.Normalize(1.f);
	Hip = Chest + -(tmp * Head.Z * RatioChestToHip);




	AGlobalDatabaseActor::GetInstance()->DevActors[0]->SetActorLocation(Eyes);
	AGlobalDatabaseActor::GetInstance()->DevActors[1]->SetActorLocation(Head);
	AGlobalDatabaseActor::GetInstance()->DevActors[2]->SetActorLocation(Neck);
	AGlobalDatabaseActor::GetInstance()->DevActors[3]->SetActorLocation(Chest);
	AGlobalDatabaseActor::GetInstance()->DevActors[4]->SetActorLocation(Hip);
	// ...
}

