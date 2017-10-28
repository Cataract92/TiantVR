// Fill out your copyright notice in the Description page of Project Settings.

#include "VRPawn_CPP.h"
#include "Components/InputComponent.h"


// Sets default values
AVRPawn_CPP::AVRPawn_CPP()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AVRPawn_CPP::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AVRPawn_CPP::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	CalculatePositions(DeltaTime);
}


void AVRPawn_CPP::CalculatePositions(float DeltaTime)
{
	UCameraComponent* Camera = FindComponentByClass<UCameraComponent>();

	if (!Camera)
	{
		AGlobalDatabaseActor::GetInstance()->PrintDebugMessage("NoCam");
		return;
	}

	FMinimalViewInfo ViewInfo;
	Camera->GetCameraView(DeltaTime, OUT ViewInfo);

	FVector EyeToHead, HeadToChest, ChestToHip;

	EyePosition.Set(ViewInfo.Location.X, ViewInfo.Location.Y- 50, ViewInfo.Location.Z);
	
	FRotator EyeRotation = ViewInfo.Rotation + FRotator(90.f, 0.f, 0.f);
	EyeToHead.X = EyePosition.Z * (1 - (1 / 0.946f));
	EyeRotation.RotateVector(EyeToHead);
	HeadPosition.Set(EyePosition.X+EyeToHead.X, EyePosition.Y+EyeToHead.Y, EyePosition.Z + EyeToHead.Z);

	FRotator ChestRotation(-EyeRotation.Pitch,EyeRotation.Yaw,EyeRotation.Roll);
	HeadToChest.X = HeadPosition.Z * (1 - 0.818f);
	ChestRotation.RotateVector(HeadToChest);
	ChestPosition.Set(HeadPosition.X + HeadToChest.X, HeadPosition.Y + HeadToChest.Y, HeadPosition.Z + HeadToChest.Z);
	//ChestPosition.Set(HeadPosition.X, HeadPosition.Y, HeadPosition.Z - HeadPosition.Z * (1 - 0.818f));
	//HipPosition.Set(ChestPosition.X, ChestPosition.Y, ChestPosition.Z - ChestPosition.Z * (1 - 0.530f));

	TArray<UActorComponent*> SphereComponents = GetComponentsByClass(UStaticMeshComponent::StaticClass());

	for (UActorComponent* Component : SphereComponents)
	{
		UStaticMeshComponent* Sphere = Cast<UStaticMeshComponent>(Component);

		if (Sphere->GetName().Equals("ChestSphere"))
		{
			Sphere->SetWorldLocation(HeadPosition);
		} 
		else if (Sphere->GetName().Equals("HipSphere"))
		{
			Sphere->SetWorldLocation(ChestPosition);
		}
		
	}

	FRotator Rotation = ViewInfo.Rotation;

	//AGlobalDatabaseActor::GetInstance()->PrintDebugMessage(Rotation.ToString());
	
	if ( Rotation.Roll < -HeadRollTolerance || Rotation.Roll > HeadRollTolerance)
		AGlobalDatabaseActor::GetInstance()->PrintDebugMessage("Rotate Neck");
}


// Called to bind functionality to input
void AVRPawn_CPP::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	check(PlayerInputComponent);

	PlayerInputComponent->BindAction("RightTrigger",IE_Pressed, this, &AVRPawn_CPP::Pressed);
	PlayerInputComponent->BindAction("RightTrigger", IE_Released, this, &AVRPawn_CPP::Released);
}

void AVRPawn_CPP::Pressed()
{
	AGlobalDatabaseActor::GetInstance()->PrintDebugMessage(FString::Printf(TEXT("Pressed")));
}

void AVRPawn_CPP::Released()
{
	AGlobalDatabaseActor::GetInstance()->PrintDebugMessage(FString::Printf(TEXT("Released")));
}
