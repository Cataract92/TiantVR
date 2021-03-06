// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CollisionQueryParams.h"
#include "CameraViewRayCaster.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TIANT_API UCameraViewRayCaster : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCameraViewRayCaster();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	uint16 GetMaxReflections() const;

private:

	APawn* PlayerPawn;

	FCollisionObjectQueryParams CollisionParameters;
	
	UPROPERTY(EditAnywhere)
	float RayCastRange = 10000.f;

	UPROPERTY(EditAnywhere)
	uint16 MaxReflections = 3;

	AActor* GetValidActorByHitResult(FHitResult& HitResult, uint16 ReflectionDepth = 0) const;
};
