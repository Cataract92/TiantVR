// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PuzzleLambdaActor.generated.h"

UENUM(BlueprintType)
enum ETriggerActionEnum
{
	TAE_CameraOverlap UMETA(DisplayName = "Camera Overlapping"),
	TAE_OnTick UMETA(DisplayName = "On Tick")
};

UENUM(BlueprintType)
enum ELambdaEnum
{
	LE_Scene1_RotateMirror UMETA(DisplayName = "Scene 1 | Rotate Mirror"),
	LE_Scene1_DoNothing UMETA(DisplayName = "Scene 1 | DoNothing")
};

USTRUCT(BlueprintType)
struct FTriggerableParams {

	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere)
	bool bUseRotation;

	UPROPERTY(EditAnywhere, meta = (EditCondition = bUseRotation))
	FVector Rotation;
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

	virtual void FireLambda(AActor* TriggeringActor, ETriggerActionEnum TriggerAction, FTriggerableParams & Params);

	virtual void RegisterLambda(AActor* TriggeringActor, AActor* TriggeredActor, ETriggerActionEnum TriggerAction);

private:
	TMap<ELambdaEnum, TFunction<void(AActor* TriggeringActor, FTriggerableParams& Params)>> LambdasMap;
	
	TMap<AActor*, TMap<ETriggerActionEnum, TArray<AActor*>>> TriggeringActorMap;

	virtual void AddLambdaDefinition(ELambdaEnum LambdaEnum, TFunction<void(AActor* TriggeringActor, FTriggerableParams& Params)> Lamda);

	virtual TFunction<void(AActor* TriggeringActor, FTriggerableParams& Params)> GetLambda(ELambdaEnum LambdaEnum);
};


