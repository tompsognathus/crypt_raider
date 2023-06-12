// Fill out your copyright notice in the Description page of Project Settings.


#include "TriggerComponent.h"

// Sets default values for this component's properties
UTriggerComponent::UTriggerComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

}

void UTriggerComponent::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void UTriggerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	AActor* Actor = GetAcceptableActor();
	if (Actor != nullptr)
	{
		// Handle interactions where the player triggers an action
		if (Actor->Tags.Contains("Player"))
		{
			// Open/close automatic doors
			if (FirstTimeTriggered)
			{
				FirstTimeTriggered = false;

				// Move all associated components
				for (UMover* Mover : Movers)
				{
					if (Mover != nullptr)
					{
						Mover->SetShouldMove(true);
						Mover->SetShouldRotate(true);
					}
					else
					{
						UE_LOG(LogTemp, Warning, TEXT("Mover is null"));
					}
				}
			}
		}
		// Handle interactions where the player releases an object on the trigger
		else
		{
			if (Actor->Tags.Contains("Released"))
			{
				// Place object on trigger
				UPrimitiveComponent* Component = Cast<UPrimitiveComponent>(Actor->GetRootComponent());
				if (Component != nullptr)
				{
					Component->SetSimulatePhysics(false);
				}
				else
				{
					UE_LOG(LogTemp, Warning, TEXT("Component is null"));
				}
				Actor->AttachToComponent(this, FAttachmentTransformRules::SnapToTargetNotIncludingScale);

				// Trigger associated movers
				if (FirstTimeTriggered)
				{
					for (UMover* Mover : Movers)
					{
						FirstTimeTriggered = false;

						if (Mover != nullptr)
						{
							Mover->SetShouldMove(true);
							Mover->SetShouldRotate(true);
						}
						else
						{
							UE_LOG(LogTemp, Warning, TEXT("Mover is null"));
						}
					}
				}
			}
		}
	}
}

// Gets the first actor that has the correct tag
AActor* UTriggerComponent::GetAcceptableActor() const
{
	TArray<AActor*> Actors;
	GetOverlappingActors(Actors);

	for (AActor* Actor : Actors)
	{
		if (Actor->Tags.Contains(TriggerName))
		{
			return Actor;
		}
	}

	return nullptr;
}

void UTriggerComponent::SetMovers(TArray<UMover*> NewMovers)
{
	Movers = NewMovers;
}