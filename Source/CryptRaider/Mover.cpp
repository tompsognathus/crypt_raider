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

	MoveDirection = MoveDirection.GetSafeNormal();

	InitialLocation = GetOwner()->GetActorLocation();
	TargetLocation = InitialLocation + MoveDirection * MoveDistance;

	InitialRotation = GetOwner()->GetActorRotation();
	TargetRotation = InitialRotation + RotationAngle * FRotator(0, 1, 0);
}


// Called every frame
void UMover::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	Move(DeltaTime);
	Rotate(DeltaTime);
}

void UMover::Move(float DeltaTime)
{
	if (ShouldMove)
	{
		FVector CurrentLocation = GetOwner()->GetActorLocation();

		if (FVector::Dist(CurrentLocation, TargetLocation) > 10)
		{
			FVector NewLocation = CurrentLocation + MoveSpeed * DeltaTime * MoveDirection;
			GetOwner()->SetActorLocation(NewLocation);
		}
		else
		{
			ShouldMove = false;
			GetOwner()->SetActorLocation(TargetLocation);

			CurrentLocation = TargetLocation;
			TargetLocation = InitialLocation;
			InitialLocation = CurrentLocation;
			MoveDirection = -MoveDirection;
		}
	}
}

void UMover::Rotate(float DeltaTime)
{
	if (ShouldRotate)
	{
		FRotator CurrentRotation = GetOwner()->GetActorRotation();

		// If the rotation hasn't passed the target rotation yet, rotate
		if (FMath::Abs(CurrentRotation.Yaw - TargetRotation.Yaw) > 10)
		{
			FRotator NewRotation = CurrentRotation + FRotator(0, FMath::Sign(RotationAngle) * RotationSpeed * DeltaTime, 0);
			GetOwner()->SetActorRotation(NewRotation);
		}
		else
		{
			ShouldRotate = false;
			GetOwner()->SetActorRotation(TargetRotation);

			CurrentRotation = TargetRotation;
			TargetRotation = InitialRotation;
			InitialRotation = CurrentRotation;
			RotationAngle = -RotationAngle;
		}

	}
}

void UMover::SetShouldMove(bool NewShouldMove)
{
	ShouldMove = NewShouldMove;
}

void UMover::SetShouldRotate(bool NewShouldRotate)
{
	ShouldRotate = NewShouldRotate;
}
