// Fill out your copyright notice in the Description page of Project Settings.

#include "Grabber.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();
	PhysicsHandle = GetPhysicsHandle();
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	// Set destination and rotation for grabbed object
	if (IsGrabbing)
	{
		FVector TargetLocation = GetComponentLocation() + GetForwardVector() * HoldDistance;
		FRotator TargetRotation = GetComponentRotation();
		PhysicsHandle->SetTargetLocationAndRotation(TargetLocation, TargetRotation);
	}
}

void UGrabber::Grab()
{
	FHitResult HitResult;

	FVector SweepStart = GetComponentLocation();
	FVector SweepEnd = SweepStart + GetForwardVector() * MaxGrabDistance;
	
	DrawDebugLine(GetWorld(), SweepStart, SweepEnd, FColor::Red);

	bool HasHit = GetWorld()->SweepSingleByChannel(
		HitResult,
		SweepStart, SweepEnd,
		FQuat::Identity,
		ECC_GameTraceChannel2,
		FCollisionShape::MakeSphere(GrabRadius)
	);

	if (HasHit)
	{
		// Grab targeted object
		PhysicsHandle->GrabComponentAtLocationWithRotation(
			HitResult.GetComponent(),
			NAME_None,
			HitResult.ImpactPoint,
			GetComponentRotation()
		);

		IsGrabbing = true;
	}
	else
	{
		IsGrabbing = false;
	}
}

void UGrabber::Release()
{
	if (IsGrabbing)
	{
		IsGrabbing = false;
		PhysicsHandle->ReleaseComponent();
	}
}

UPhysicsHandleComponent* UGrabber::GetPhysicsHandle() const
{
	UPhysicsHandleComponent* Result = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (PhysicsHandle == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("No PhysicsHandleComponent found on %s"), *GetOwner()->GetName());
	}

	return Result;
}
