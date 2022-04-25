// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Bar.generated.h"

class UCapsuleComponent;
class USphereComponent;
class UStaticMeshComponent;
class URadialForceComponent;
class USceneComponent;

UCLASS()
class ACTIONROUGELIKE_API ABar : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABar(const FObjectInitializer& ObjectInitializer);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	USceneComponent* SceneComp;

	UPROPERTY(EditAnywhere)
	USphereComponent* SphereComp;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* BarMeshComp;

	UPROPERTY(EditAnywhere)
	UCapsuleComponent* CapsComp;

	//UPROPERTY(BlueprintReadWrite)
	//URadialForceComponent* RadialForceComp;

	UPROPERTY()
	float Radius = 500.f;

	UPROPERTY()
	FString Target = "Target";

public:		
	UFUNCTION()
	void SweepArea();

	UFUNCTION()
	void OnScreenDebugMsg(AActor* OtherActor);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void OnCompHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);


};
