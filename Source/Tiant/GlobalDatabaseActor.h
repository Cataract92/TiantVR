// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine.h"
#include "GameFramework/Actor.h"
#include "Runtime/Engine/Classes/Engine/TextRenderActor.h"
#include "EngineUtils.h"
#include "TiantCharacter.h"
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

	ATextRenderActor* GetTextRenderer();

	static AGlobalDatabaseActor* GetInstance();

	static ATiantCharacter* GetTiant();

private:
	UPROPERTY(EditAnywhere)
	ATextRenderActor* TextRenderer;
};
