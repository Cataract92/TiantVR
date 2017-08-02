// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PuzzleLambdaActor.h"
#include "TriggerableComponent.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TIANT_API UTriggerableComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTriggerableComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:

	UPROPERTY(EditAnywhere)
	FTriggerableParams Parameter;

	UPROPERTY(EditAnywhere)
	AActor* TriggeringActor;

	UPROPERTY(EditAnywhere)
	TEnumAsByte<ETriggerActionEnum> TriggeringAction;

	UPROPERTY(EditAnywhere)
	TEnumAsByte<ELambdaEnum> LambdaFunction;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	ETriggerActionEnum GetTriggeringAction();

	ELambdaEnum GetLambdaEnum();

	FTriggerableParams& GetPredefinedParameters();
};