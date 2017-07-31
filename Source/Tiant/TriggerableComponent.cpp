// Fill out your copyright notice in the Description page of Project Settings.

#include "TriggerableComponent.h"
#include "GlobalDatabaseActor.h"
#include <functional>


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

	APuzzleLambdaActor::GetInstance()->RegisterLambda(TriggeringActor, GetOwner(), TriggeringAction);
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

ELambdaEnum UTriggerableComponent::GetLambdaEnum()
{
	return LambdaFunction;
}

bool UTriggerableComponent::IsUsingPredefinedParameters()
{
	return bUsePredefinedParameters;
}
FTriggerableParams& UTriggerableComponent::GetPredefinedParameters()
{
	return Parameter;
}

