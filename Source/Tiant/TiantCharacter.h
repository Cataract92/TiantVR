// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "TiantCharacter.generated.h"

UCLASS()
class TIANT_API ATiantCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ATiantCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void OrderUse(AActor* Target);

	void PossessedBy(AController* NewController) override;

private:

	UPROPERTY(EditAnywhere)
	UBehaviorTree* BehaviorTree;
	UBehaviorTreeComponent* BehaviorTreeComponent;
	UBlackboardComponent* BlackboardComponent;

};