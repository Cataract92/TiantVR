// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpeechRecognition.h"
#include "SpeechRecognitionActor.h"
#include "GlobalDatabaseActor.h"
#include "AIController.h"
#include "MySpeechRecognitionActor.generated.h"

USTRUCT(BlueprintType)
struct FCustomPhraseStruct
{

	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(EditAnywhere)
	FString Phrase;

	UPROPERTY(EditAnywhere)
	EPhraseRecognitionTolerance Tolerance;
};


UCLASS()
class TIANT_API AMySpeechRecognitionActor : public ASpeechRecognitionActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMySpeechRecognitionActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called when the game starts or when spawned
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason);

	UFUNCTION()
	void OnWordSpoken(FRecognisedPhrases phrases);

	UFUNCTION()
	void OnUnregPhrase();

	static AMySpeechRecognitionActor* GetInstance();

private:

	UPROPERTY(EditAnywhere)
	TArray<FCustomPhraseStruct> Phrases;
};
