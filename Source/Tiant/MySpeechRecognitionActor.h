// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpeechRecognition.h"
#include "SpeechRecognitionActor.h"
#include "Runtime/Engine/Classes/Engine/TextRenderActor.h"
#include "MySpeechRecognitionActor.generated.h"

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

	void OnWordSpoken(FRecognisedPhrases phrases);
	void OnUnregPhrase();

private:

	UPROPERTY(EditAnywhere)
	ATextRenderActor* TextRenderer;
};
