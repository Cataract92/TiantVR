// Fill out your copyright notice in the Description page of Project Settings.

#include "MySpeechRecognitionActor.h"

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
	OnUnknownPhrase.AddDynamic(this, &AMySpeechRecognitionActor::OnUnregPhrase);
	
	if (Init(ESpeechRecognitionLanguage::VE_English)) {
		
		// set config params
		SetConfigParam("-vad_prespeech", ESpeechRecognitionParamType::VE_INTEGER, "10");
		SetConfigParam("-vad_postspeech", ESpeechRecognitionParamType::VE_INTEGER, "10");
		SetConfigParam("-agc", ESpeechRecognitionParamType::VE_STRING, "noise");
		SetConfigParam("-beam", ESpeechRecognitionParamType::VE_FLOAT, "1e-60");

		TArray<FRecognitionPhrase> wordList;
		wordList.Add(FRecognitionPhrase(FString("reset"), EPhraseRecognitionTolerance::VE_3));
		wordList.Add(FRecognitionPhrase(FString("go there"), EPhraseRecognitionTolerance::VE_5));
		EnableKeywordMode(wordList);
		AGlobalDatabaseActor* DBActor = AGlobalDatabaseActor::GetInstance();
			
		DBActor->PrintDebugMessage("ASpeechRecogTestActor:Init success");
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

void AMySpeechRecognitionActor::OnWordSpoken(FRecognisedPhrases phrases)
{
	TArray<FString> phraseArray = phrases.phrases;
	FString phrase;
	for (auto& phrase : phraseArray)
	{
		AGlobalDatabaseActor::GetInstance()->PrintDebugMessage(phrase);
	}
}

void AMySpeechRecognitionActor::OnUnregPhrase() {
	AGlobalDatabaseActor::GetInstance()->PrintDebugMessage("Unreg Phrase");
}