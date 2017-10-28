// Fill out your copyright notice in the Description page of Project Settings.

#include "MySpeechRecognitionActor.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "TriggerableComponent.h"


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
		for (FCustomPhraseStruct Phrase : Phrases)
		{
			wordList.Add(FRecognitionPhrase(Phrase.Phrase, Phrase.Tolerance));
		}
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
		AGlobalDatabaseActor::GetInstance()->PrintDebugMessage("Reg Phrase: "+phrase);

		if (phrase.Equals("there"))
		{
			UCameraComponent* Camera = GetWorld()->GetFirstPlayerController()->GetPawn()->FindComponentByClass<UCameraComponent>();

			if (Camera)
			{
				FMinimalViewInfo ViewInfo;
				Camera->GetCameraView(GetWorld()->GetDeltaSeconds(), OUT ViewInfo);

				FHitResult HitResult;
				GetWorld()->LineTraceSingleByObjectType(OUT HitResult, ViewInfo.Location, ViewInfo.Location + ViewInfo.Rotation.Vector() * 10000, FCollisionObjectQueryParams());
				FVector HitLocation = HitResult.Location;

				ATiantCharacter* TiantCharacter = AGlobalDatabaseActor::GetInstance()->GetTiant();
				AAIController* Controller = Cast<AAIController>(TiantCharacter->GetController());

				EPathFollowingRequestResult::Type Result = Controller->MoveToLocation(HitLocation);
			}
		}
		else if (phrase.Equals("use"))
		{
			UCameraComponent* Camera = GetWorld()->GetFirstPlayerController()->GetPawn()->FindComponentByClass<UCameraComponent>();

			if (Camera)
			{
				FMinimalViewInfo ViewInfo;
				Camera->GetCameraView(GetWorld()->GetDeltaSeconds(), OUT ViewInfo);

				FHitResult HitResult;
				GetWorld()->LineTraceSingleByObjectType(OUT HitResult, ViewInfo.Location, ViewInfo.Location + ViewInfo.Rotation.Vector() * 10000, FCollisionObjectQueryParams());
			
				if (!HitResult.GetActor() || !HitResult.GetActor()->FindComponentByClass<UTriggerableComponent>())
					return;

				AGlobalDatabaseActor::GetInstance()->GetTiant()->OrderUse(HitResult.GetActor());
			}
		}
	}
}

void AMySpeechRecognitionActor::OnUnregPhrase() {
	//AGlobalDatabaseActor::GetInstance()->PrintDebugMessage("Unreg Phrase");
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
