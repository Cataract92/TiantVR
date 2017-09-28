// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GlobalDatabaseActor.h"
#include "EngineUtils.h"
#include "PuzzleLambdaActor.generated.h"

UENUM(BlueprintType)
enum ETriggerActionEnum
{
	TAE_CameraStartOverlapp UMETA(DisplayName = "Camera Start Overlapping"),
	TAE_CameraStopOverlapp UMETA(DisplayName = "Camera Stop Overlapping"),
	TAE_CameraIsOverlapping UMETA(DisplayName = "Camera Is Overlapping"),
	TAE_OnTick UMETA(DisplayName = "On Tick"),
	TAE_ViewRayCastHit UMETA(DisplayName = "On View-RayCast Hit"),	TAE_NotSet UMETA(DisplayName = "Not Set | Do not use")
};

UENUM(BlueprintType)
enum ELambdaEnum
{
	LE_Scene1_RotateMirror UMETA(DisplayName = "Scene 1 | Rotate Mirror"),
	LE_Scene1_RaiseTable UMETA(DisplayName = "Scene 1 | Raise Table"),
	LE_Scene1_DoNothing UMETA(DisplayName = "Scene 1 | DoNothing")
};

USTRUCT(BlueprintType)
struct FTriggerableParams {

	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(EditAnywhere, meta = (EditCondition = bUseVectors))
	TArray<FVector> Vectors;

	UPROPERTY(EditAnywhere, meta = (EditCondition = bUseActors))
	TArray<AActor*> Actors;

	float DeltaTime; //Used by OnTick

	ETriggerActionEnum TriggerAction;

	FTriggerableParams()
	{
		this->TriggerAction = ETriggerActionEnum::TAE_NotSet;
	}

	FTriggerableParams(ETriggerActionEnum TriggerAction)
	{
		this->TriggerAction = TriggerAction;
	}

	static void SetParameter(FTriggerableParams& Parameter, FTriggerableParams& PredefinedParameter)
	{
		if (PredefinedParameter.bUseVectors)
		{
			Parameter.Vectors = PredefinedParameter.Vectors;
		}

	}

private:
	UPROPERTY(EditAnywhere)
	bool bUseVectors;

	UPROPERTY(EditAnywhere)
	bool bUseActors;
};

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

	virtual void FireLambda(AActor* TriggeringActor, FTriggerableParams& Params);

	virtual void RegisterLambda(AActor* TriggeringActor, AActor* TriggeredActor, ETriggerActionEnum TriggerAction);

	static APuzzleLambdaActor* GetInstance();

private:
	TMap<ELambdaEnum, TFunction<void(AActor* TriggeringActor, AActor* TriggeredActor, FTriggerableParams& Params)>> LambdasMap;
	
	TMap<AActor*, TMap<ETriggerActionEnum, TArray<AActor*>>> TriggeringActorMap;


	virtual void AddLambdaDefinition(ELambdaEnum LambdaEnum, TFunction<void(AActor* TriggeringActor, AActor* TriggeredActor, FTriggerableParams& Params)> Lamda);

	virtual TFunction<void(AActor* TriggeringActor, AActor* TriggeredActor, FTriggerableParams& Params)> GetLambda(ELambdaEnum LambdaEnum);
};


