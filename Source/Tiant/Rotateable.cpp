// Fill out your copyright notice in the Description page of Project Settings.

#include "Rotateable.h"


// Sets default values for this component's properties
URotateable::URotateable()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void URotateable::BeginPlay()
{
	Super::BeginPlay();

	TriggeringActor = GetWorld()->GetFirstPlayerController()->GetPawn();
	// ...
	
}


// Called every frame
void URotateable::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (TriggerPlate->IsOverlappingActor(TriggeringActor)) {
		GetOwner()->SetActorRotation(FRotator(0.f, -30.f, -90.f));
	}
	else {
		GetOwner()->SetActorRotation(FRotator(0.f, 0.f, -90.f));
	}
	
}

