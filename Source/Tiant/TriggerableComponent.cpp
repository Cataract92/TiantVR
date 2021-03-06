// Fill out your copyright notice in the Description page of Project Settings.

#include "TriggerableComponent.h"
#include <functional>
#include "PuzzleLambdaActor.h"


// Sets default values for this component's properties
UTriggerableComponent::UTriggerableComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UTriggerableComponent::BeginPlay()
{
	Super::BeginPlay();

	if (bDontUsePlayerPawn)
	{
		APuzzleLambdaActor::GetInstance()->RegisterLambda(this, TriggeringAction);
	} else 
	{
		TriggeringActor = GetWorld()->GetFirstPlayerController()->GetPawn();
		APuzzleLambdaActor::GetInstance()->RegisterLambda(this, TriggeringAction);
	}
}



// Called every frame
void UTriggerableComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}


ETriggerActionEnum UTriggerableComponent::GetTriggeringAction()
{
	return TriggeringAction;
}

AActor* UTriggerableComponent::GetTriggeringActor()
{
	return TriggeringActor;
}

ELambdaEnum UTriggerableComponent::GetLambdaEnum()
{
	return LambdaFunction;
}

FTriggerableParams& UTriggerableComponent::GetPredefinedParameters()
{
	return Parameter;
}

void UTriggerableComponent::Enable(bool Enable)
{
	this->bEnable = Enable;
}

bool UTriggerableComponent::IsEnabled()
{
	return this->bEnable;
}

