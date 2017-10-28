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

	static AGlobalDatabaseActor* GetInstance();

private:
	UPROPERTY(EditAnywhere)
	ATextRenderActor* TextRenderer;

	URunebergVR_Gestures_Database* GesturesDatabase;

	UAudioComponent* AudioComponent;

	USoundWave* GetSoundWaveFromFile(const FString& filePath) const;
};