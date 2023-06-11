// Fill out your copyright notice in the Description page of Project Settings.

#include "Grabber.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"

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

	UPhysicsHandleComponent* PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (PhysicsHandle != nullptr)
	{

	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("PhysicsHandleComponent is nullptr"));
	}
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

void UGrabber::Grab()
{
	FHitResult HitResult;

	FVector DebugLineStart = GetComponentLocation();
	FVector DebugLineEnd = DebugLineStart + GetForwardVector() * MaxGrabDistance;
	
	DrawDebugLine(GetWorld(), DebugLineStart, DebugLineEnd, FColor::Red);

	bool HasHit = GetWorld()->SweepSingleByChannel(
		HitResult,
		DebugLineStart, DebugLineEnd,
		FQuat::Identity,
		ECC_GameTraceChannel2,
		FCollisionShape::MakeSphere(GrabRadius)
	);

	if (HasHit)
	{
		AActor* HitActor = HitResult.GetActor();
		FVector ImpactPt = HitResult.ImpactPoint;

		DrawDebugSphere(GetWorld(), ImpactPt, 10, 10, FColor::Red, false, 5);

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
	}
	else
	{

	}

}

