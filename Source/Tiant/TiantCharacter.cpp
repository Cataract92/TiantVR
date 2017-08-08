// Fill out your copyright notice in the Description page of Project Settings.

#include "TiantCharacter.h"
#include "AIController.h"
#include "Engine/Engine.h"
#include "Runtime/ActorSequence/Private/ActorSequencePrivatePCH.h"


// Sets default values
ATiantCharacter::ATiantCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATiantCharacter::BeginPlay()
{
	Super::BeginPlay();

}

bool bTest = true;

// Called every frame
void ATiantCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ATiantCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}
