// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Mover.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CRYPTRAIDER_API UMover : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UMover();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	UPROPERTY(EditAnywhere)
	FVector InitialLocation;
	
	UPROPERTY(EditAnywhere)
	FVector TargetLocation;

	// Vector that determines the direction of movement. Will be normalized in code.
	UPROPERTY(EditAnywhere)
	FVector MoveDirection;

	// Distance the object will move from its initial location.
	UPROPERTY(EditAnywhere)
	float MoveDistance = 1000;
	
	UPROPERTY(EditAnywhere)
	float MoveSpeed = 10;
	
	UPROPERTY(EditAnywhere)
	bool ShouldMove = false;


};
