// Fill out your copyright notice in the Description page of Project Settings.


#include "Mover.h"

// Sets default values for this component's properties
UMover::UMover()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UMover::BeginPlay()
{
	Super::BeginPlay();

	InitialLocation = GetOwner()->GetActorLocation();
	MoveDirection = MoveDirection.GetSafeNormal();

	UE_LOG(LogTemp, Display, TEXT("Computing TargetLocation"));

	TargetLocation = InitialLocation + MoveDirection * MoveDistance;
}


// Called every frame
void UMover::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (ShouldMove)
	{
		FVector CurrentLocation = GetOwner()->GetActorLocation();

		UE_LOG(LogTemp, Display, TEXT("Distance = %f"), FVector::Dist(CurrentLocation, TargetLocation));
		if (FVector::Dist(CurrentLocation, TargetLocation) > 1)
		{
			UE_LOG(LogTemp, Display, TEXT("Moving"));
			FVector NewLocation = CurrentLocation + MoveSpeed * DeltaTime * MoveDirection;
			GetOwner()->SetActorLocation(NewLocation);
		}
		else
		{
			UE_LOG(LogTemp, Display, TEXT("Inside Else"));
			ShouldMove = false;
			GetOwner()->SetActorLocation(TargetLocation);

			CurrentLocation = TargetLocation;
			TargetLocation = InitialLocation;
			InitialLocation = CurrentLocation;
			MoveDirection = -MoveDirection;
		}
	}
}

