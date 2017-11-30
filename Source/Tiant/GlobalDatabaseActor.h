// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine.h"
#include "GameFramework/Actor.h"
#include "Runtime/Engine/Classes/Engine/TextRenderActor.h"
#include "EngineUtils.h"
#include "TiantCharacter.h"
#include "RunebergVR_Gestures_Database.h"
#include "GlobalDatabaseActor.generated.h"



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
	TAE_ViewRayCastHit UMETA(DisplayName = "On View-RayCast Hit"), TAE_NotSet UMETA(DisplayName = "Not Set | Do not use")
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
struct FTriggerableParams
{

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
class TIANT_API AGlobalDatabaseActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGlobalDatabaseActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void PrintDebugMessage(FString Message);

	ATextRenderActor* GetTextRenderer() const;
	URunebergVR_Gestures_Database* GetGestureDatabase() const;
	void PlaySoundAtLocation(FVector Location, const FString& AudioFile) const;
	ATiantCharacter* GetTiant();

	UPROPERTY(EditAnywhere)
	TArray<AActor*> DevActors;

	static AGlobalDatabaseActor* GetInstance();

private:
	UPROPERTY(EditAnywhere)
	ATextRenderActor* TextRenderer;

	URunebergVR_Gestures_Database* GesturesDatabase;

	UAudioComponent* AudioComponent;

	USoundWave* GetSoundWaveFromFile(const FString& filePath) const;
};