// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "MySpeechRecognitionActor.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "TriggerableComponent.h"
#include "PuzzleLambdaActor.h"


#define AddDynamic( UserObject, FuncName ) __Internal_AddDynamic( UserObject, FuncName, STATIC_FUNCTION_FNAME( TEXT( #FuncName ) ) )

// Sets default values
AMySpeechRecognitionActor::AMySpeechRecognitionActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AMySpeechRecognitionActor::BeginPlay()
{
	Super::BeginPlay();
	
	OnWordsSpoken.AddDynamic(this, &AMySpeechRecognitionActor::OnWordSpoken);
	
	if (Init(ESpeechRecognitionLanguage::VE_English)) {
		
		// set config params
		SetConfigParam("-vad_prespeech", ESpeechRecognitionParamType::VE_INTEGER, "10");
		SetConfigParam("-vad_postspeech", ESpeechRecognitionParamType::VE_INTEGER, "10");
		SetConfigParam("-agc", ESpeechRecognitionParamType::VE_STRING, "noise");
		SetConfigParam("-beam", ESpeechRecognitionParamType::VE_FLOAT, "1e-60");

		TArray<FRecognitionPhrase> wordList;
		for (FCustomPhraseStruct Phrase : Phrases)
		{
			wordList.Add(FRecognitionPhrase(Phrase.Phrase, Phrase.Tolerance));
			PhrasesMap.Add(Phrase.Phrase, Phrase);
		}
		EnableKeywordMode(wordList);
	} else {
		AGlobalDatabaseActor::GetInstance()->PrintDebugMessage("ASpeechRecogTestActor:Init failed");
	}
}

// Called every frame
void AMySpeechRecognitionActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Call shutdown on listener
void AMySpeechRecognitionActor::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Shutdown();
}

void AMySpeechRecognitionActor::OnWordSpoken(FRecognisedPhrases Phrases)
{
	TArray<FString> PhraseArray = Phrases.phrases;
	for (auto& Phrase : PhraseArray)
	{
		FTriggerableParams PhraseRecognitionParams(ETriggerActionEnum::TAE_OnPhraseRecognition);
		PhraseRecognitionParams.Strings[0] = Phrase;
		APuzzleLambdaActor::GetInstance()->FireLambda(GetWorld()->GetFirstPlayerController()->GetPawn(), PhraseRecognitionParams);
	}
}

AMySpeechRecognitionActor* AMySpeechRecognitionActor::GetInstance()
{
	// Prevents Nullptrexception in Iterator if this is called before or while Gameinitializaion
	if (!GEngine->GameViewport->GetWorld()) return nullptr;

	// Iterate through all GlobalDatabaseActors and return the first one found
	// (only one should exist)
	for (TActorIterator<AMySpeechRecognitionActor> ActorItr(GEngine->GameViewport->GetWorld()); ActorItr; ++ActorItr)
	{
		return *ActorItr;
	}

	// If no GDActor is found return null
	return nullptr;
}
