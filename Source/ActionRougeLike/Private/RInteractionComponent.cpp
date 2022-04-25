// Fill out your copyright notice in the Description page of Project Settings.

/*
#include "RInteractionComponent.h"
//#include "SGameplayInterface.h"

// Sets default values for this component's properties
URInteractionComponent::URInteractionComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void URInteractionComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void URInteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void URInteractionComponent::PrimaryInteract(){	

	AActor* MyOwner = GetOwner();
	FVector EyeLocation;
	FRotator EyeRotation;

	if (MyOwner) {
		MyOwner->GetActorEyesViewPoint(EyeLocation, EyeRotation);
	}

	FHitResult HitResult;
	FVector Start = EyeLocation;
	FVector End = EyeLocation + (EyeRotation.Vector() * 1000);
	FCollisionObjectQueryParams ObjectQueryParams;
	ObjectQueryParams.AddObjectTypesToQuery(ECC_WorldDynamic);
	GetWorld()->LineTraceSingleByObjectType(HitResult,Start,End,ObjectQueryParams);

	// To get the Actor that was hit and call the interaction function in gameplay interface
	AActor* HitActor = HitResult.GetActor();
	if(HitActor)
	{
		//if (HitActor->Implements<ISGameplayInterface>())
		//{

		//}
	}
	

}

*/