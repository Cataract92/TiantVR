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
