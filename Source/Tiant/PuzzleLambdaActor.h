// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine.h"
#include "GameFramework/Actor.h"
#include "GlobalDatabaseActor.h"
#include "TriggerableComponent.h"
#include "PuzzleLambdaActor.generated.h"

UCLASS()
class TIANT_API APuzzleLambdaActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APuzzleLambdaActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;	

	UFUNCTION(BlueprintCallable)
	virtual void FireLambda(AActor* TriggeringActor, FTriggerableParams& Params);

	virtual void RegisterLambda(UTriggerableComponent* TriggerableComponent, ETriggerActionEnum TriggerAction);

	UFUNCTION(BlueprintCallable)
	static APuzzleLambdaActor* GetInstance();

private:
	TMap<ELambdaEnum, TFunction<void(AActor* TriggeringActor, AActor* TriggeredActor, FTriggerableParams& Params)>> LambdasMap;

	TMap<ETriggerActionEnum, TArray<UTriggerableComponent*>> ActionMap;

	virtual void AddLambdaDefinition(ELambdaEnum LambdaEnum, TFunction<void(AActor* TriggeringActor, AActor* TriggeredActor, FTriggerableParams& Params)> Lamda);

	virtual TFunction<void(AActor* TriggeringActor, AActor* TriggeredActor, FTriggerableParams& Params)> GetLambda(ELambdaEnum LambdaEnum);
};


