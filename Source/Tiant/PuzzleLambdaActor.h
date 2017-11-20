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
	TAE_TiantStartOverlapp UMETA(DisplayName = "Tiant Start Overlapping"),
	TAE_TiantStopOverlapp UMETA(DisplayName = "Tiant Stop Overlapping"),
	TAE_TiantIsOverlapping UMETA(DisplayName = "Tiant Is Overlapping"),
	TAE_OnTick UMETA(DisplayName = "On Tick"),
	TAE_OnTiantInteraction UMETA(DisplayName = "On Tiant Interaction"),
	TAE_ViewRayCastHit UMETA(DisplayName = "On View-RayCast Hit"),	TAE_NotSet UMETA(DisplayName = "Not Set | Do not use")
};

UENUM(BlueprintType)
enum ELambdaEnum
{
	LE_Scene1_InitTiant UMETA(DisplayName = "Scene 1 | Init Tiant"),
	LE_Scene1_MoveWall UMETA(DisplayName = "Scene 1 | Move Wall"),
	LE_Scene1_MoveWall2 UMETA(DisplayName = "Scene 1 | Move Wall2"),
	LE_Scene1_RotateMirror UMETA(DisplayName = "Scene 1 | Rotate Mirror"),
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

	AActor* TriggeredActor = nullptr;

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
		if (PredefinedParameter.bUseActors)
		{
			Parameter.Actors = PredefinedParameter.Actors;
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

	UFUNCTION(BlueprintCallable)
	virtual void FireLambda(AActor* TriggeringActor, FTriggerableParams& Params);

	virtual void RegisterLambda(AActor* TriggeringActor, AActor* TriggeredActor, ETriggerActionEnum TriggerAction);

	UFUNCTION(BlueprintCallable)
	static APuzzleLambdaActor* GetInstance();

private:
	TMap<ELambdaEnum, TFunction<void(AActor* TriggeringActor, AActor* TriggeredActor, FTriggerableParams& Params)>> LambdasMap;
	
	TMap<AActor*, TMap<ETriggerActionEnum, TArray<AActor*>>> TriggeringActorMap;


	virtual void AddLambdaDefinition(ELambdaEnum LambdaEnum, TFunction<void(AActor* TriggeringActor, AActor* TriggeredActor, FTriggerableParams& Params)> Lamda);

	virtual TFunction<void(AActor* TriggeringActor, AActor* TriggeredActor, FTriggerableParams& Params)> GetLambda(ELambdaEnum LambdaEnum);
};


