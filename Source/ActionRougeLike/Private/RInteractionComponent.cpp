// Fill out your copyright notice in the Description page of Project Settings.


#include "RInteractionComponent.h"
#include "SGameplayInterface.h"
#include "DrawDebugHelpers.h"

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
	//UE_LOG(LogTemp, Warning, TEXT("PrimaryInteract HitActor->Implements"));
	AActor* MyOwner = GetOwner();
	FVector EyeLocation;
	FRotator EyeRotation;

	if(MyOwner){
		//UE_LOG(LogTemp, Warning, TEXT("MyOwner"));
		MyOwner->GetActorEyesViewPoint(EyeLocation, EyeRotation);
	}

	TArray<FHitResult> HitResult;
	FVector Start = EyeLocation;
	FVector End = EyeLocation + (EyeRotation.Vector() * 1000);
	FCollisionObjectQueryParams ObjectQueryParams;
	ObjectQueryParams.AddObjectTypesToQuery(ECC_WorldDynamic);
	FCollisionShape Shape;
	float Radius = 30.f;
	Shape.SetSphere(Radius);
	bool bBlockingHit = GetWorld()->SweepMultiByObjectType(HitResult,Start,End,FQuat::Identity,ObjectQueryParams,Shape);
	FColor LineColor = bBlockingHit ? FColor::Green : FColor::Red;
	
	for(FHitResult Hit : HitResult){
		//UE_LOG(LogTemp, Warning, TEXT("Hit HitResult: s% "), *Hit.GetActor()->GetName());
		AActor* HitActor = Hit.GetActor();
		//UE_LOG(LogTemp, Warning, TEXT("Hit Result: s% "), *HitActor->GetName());
		if(HitActor){
			//UE_LOG(LogTemp, Warning, TEXT("HitActor"));
			if (HitActor->Implements<USGameplayInterface>()){
				//UE_LOG(LogTemp, Warning, TEXT("HitActor->Implements"));
				APawn* MyPawn = Cast<APawn>(MyOwner);
				ISGameplayInterface::Execute_Interact(HitActor, MyPawn);
				break;
			}
		}
		DrawDebugSphere(GetWorld(), Hit.ImpactPoint, Radius, 32, LineColor,false, 2.0f);
	}
	DrawDebugLine(GetWorld(), EyeLocation, End, LineColor, false, 2.0f, 0, 2.0f);
}

