// Fill out your copyright notice in the Description page of Project Settings.

#include "GlobalDatabaseActor.h"


// Sets default values
AGlobalDatabaseActor::AGlobalDatabaseActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AGlobalDatabaseActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGlobalDatabaseActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//AGlobalDatabaseActor::GetInstance()->PrintDebugMessage("Tick");

}

void AGlobalDatabaseActor::PrintDebugMessage(FString Message)
{
	// Check is important due the use of Singleton, which could return nullptr
	// and to check if TextRenderer is not null
	if (this != nullptr && TextRenderer)
		TextRenderer->GetTextRender()->SetText(FText::FromString(TextRenderer->GetTextRender()->Text.ToString() + "\n" + Message));
}

ATextRenderActor* AGlobalDatabaseActor::GetTextRenderer()
{
	return TextRenderer;
}



AGlobalDatabaseActor* AGlobalDatabaseActor::GetInstance()
{
	// Prevents Nullptrexception in Iterator if this is called before or while Gameinitializaion
	if (!GEngine->GameViewport->GetWorld()) return nullptr;
	
	// Iterate through all GlobalDatabaseActors and return the first one found
	// (only one should exist)
	for (TActorIterator<AGlobalDatabaseActor> ActorItr(GEngine->GameViewport->GetWorld()); ActorItr; ++ActorItr) {
		return *ActorItr;
	}
	
	// If no GDActor is found return null
	return nullptr;
	
}

