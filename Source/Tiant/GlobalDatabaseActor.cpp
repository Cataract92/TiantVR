// Fill out your copyright notice in the Description page of Project Settings.

#include "GlobalDatabaseActor.h"
#include "GestureComponent.h"


// Sets default values
AGlobalDatabaseActor::AGlobalDatabaseActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	AudioComponent = CreateDefaultSubobject<UAudioComponent>("Audio");
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
}

int count = 0;

void AGlobalDatabaseActor::PrintDebugMessage(FString Message)
{
	if (count++ >= 100)
	{
		count = 0;
		TextRenderer->GetTextRender()->SetText(FText::FromString(Message));
	}

	// Check is important due the use of Singleton, which could return nullptr
	// and to check if TextRenderer is not null
	if (this != nullptr && TextRenderer)
		TextRenderer->GetTextRender()->SetText(FText::FromString(TextRenderer->GetTextRender()->Text.ToString() + "\n" + Message));

}

ATextRenderActor* AGlobalDatabaseActor::GetTextRenderer() const
{
	return TextRenderer;
}

void AGlobalDatabaseActor::PlaySoundAtLocation(FVector Location,const FString& AudioFile) const
{
	USoundWave* Sound = this->GetSoundWaveFromFile(FPaths::ProjectDir()+AudioFile);

	if (!Sound)
	{
		AGlobalDatabaseActor::GetInstance()->PrintDebugMessage("Error Sound");
	}

	UGameplayStatics::PlaySoundAtLocation(GEngine->GameViewport->GetWorld(), Sound, Location);
}

USoundWave* AGlobalDatabaseActor::GetSoundWaveFromFile(const FString& filePath) const
{
	USoundWave* sw = NewObject<USoundWave>(USoundWave::StaticClass());

	if (!sw)
		return nullptr;

	TArray < uint8 > rawFile;

	FFileHelper::LoadFileToArray(rawFile, filePath.GetCharArray().GetData());
	FWaveModInfo WaveInfo;

	if (WaveInfo.ReadWaveInfo(rawFile.GetData(), rawFile.Num()))
	{
		sw->InvalidateCompressedData();

		sw->RawData.Lock(LOCK_READ_WRITE);
		void* LockedData = sw->RawData.Realloc(rawFile.Num());
		FMemory::Memcpy(LockedData, rawFile.GetData(), rawFile.Num());
		sw->RawData.Unlock();

		int32 DurationDiv = *WaveInfo.pChannels * *WaveInfo.pBitsPerSample * *WaveInfo.pSamplesPerSec;
		if (DurationDiv)
		{
			sw->Duration = *WaveInfo.pWaveDataSize * 8.0f / DurationDiv;
		}
		else
		{
			sw->Duration = 0.0f;
		}
		sw->SampleRate = *WaveInfo.pSamplesPerSec;
		sw->NumChannels = *WaveInfo.pChannels;
		sw->RawPCMDataSize = WaveInfo.SampleDataSize;
		sw->SoundGroup = ESoundGroup::SOUNDGROUP_Default;
	}
	else
	{
		return nullptr;
	}

	return sw;
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

ATiantCharacter* AGlobalDatabaseActor::GetTiant()
{
	// Prevents Nullptrexception in Iterator if this is called before or while Gameinitializaion
	if (!GEngine->GameViewport->GetWorld()) return nullptr;

	// Iterate through all GlobalDatabaseActors and return the first one found
	// (only one should exist)
	for (TActorIterator<ATiantCharacter> ActorItr(GEngine->GameViewport->GetWorld()); ActorItr; ++ActorItr)
	{
		return *ActorItr;
	}

	// If no GDActor is found return null
	return nullptr;

}

AGestureRecognitionActor* AGlobalDatabaseActor::GetGestureRecognitionActor()
{
	// Prevents Nullptrexception in Iterator if this is called before or while Gameinitializaion
	if (!GEngine->GameViewport->GetWorld()) return nullptr;

	// Iterate through all GlobalDatabaseActors and return the first one found
	// (only one should exist)
	for (TActorIterator<AGestureRecognitionActor> ActorItr(GEngine->GameViewport->GetWorld()); ActorItr; ++ActorItr)
	{
		return *ActorItr;
	}

	// If no GDActor is found return null
	return nullptr;
}

